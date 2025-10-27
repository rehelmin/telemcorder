#include "bmpxxx.h"
#include "stm32f1xx_hal.h"

#define BMP_CS_LOW 	HAL_GPIO_WritePin(NBMP_CS_GPIO_Port, NBMP_CS_Pin, GPIO_PIN_RESET)
#define BMP_CS_HI 	HAL_GPIO_WritePin(NBMP_CS_GPIO_Port, NBMP_CS_Pin, GPIO_PIN_SET)

static HAL_StatusTypeDef BMP_WriteReg(BMP_HandleTypeDef *hbmp, uint8_t reg, uint8_t data)
{
	uint8_t tx_data[2] = {reg, data};
	HAL_StatusTypeDef status;

	BMP_CS_LOW;
	status = HAL_SPI_Transmit(hbmp->hspi, tx_data, 2, 100);
	BMP_CS_HI;

	return status;
}

static HAL_StatusTypeDef BMP_ReadReg(BMP_HandleTypeDef *hbmp, uint8_t reg, uint8_t *data)
{
	const uint8_t READ_FLAG = 1 << 7;
	uint8_t tx_data[2] = {READ_FLAG | reg, 0xFF};
	uint8_t rx_data[2];
	HAL_StatusTypeDef status;

	BMP_CS_LOW;
	status = HAL_SPI_TransmitReceive(hbmp->hspi, tx_data, rx_data, 2, 100);
	BMP_CS_HI;

	if (status == HAL_OK) {
		*data = rx_data[1];
	}

	return status;
}

int BMP_Init(BMP_HandleTypeDef *hbmp, SPI_HandleTypeDef *hspi)
{
	HAL_StatusTypeDef status;
	uint8_t chip_id, reg_data;
	uint32_t timeout;

	hbmp->hspi = hspi;

	hbmp->state = BMP_STATE_RESET;

	// Step 1: Activate SPI interface by performing a register read
	status = BMP_ReadReg(hbmp, BMP384_CHIP_ID_ADDR, &chip_id);
	if (status != HAL_OK || chip_id != BMP384_CHIP_ID_VALUE) {
		hbmp->state = BMP_STATE_ERROR;
		return TELEM_ERR;
	}

	// Step 2: Verify SPI interface is active
	status = BMP_ReadReg(hbmp, BMP384_CHIP_ID_ADDR, &chip_id);
	if (status != HAL_OK || chip_id != BMP384_CHIP_ID_VALUE) {
		hbmp->state = BMP_STATE_ERROR;
		return TELEM_ERR;
	}

	// Step 3: Soft reset
	status = BMP_WriteReg(hbmp, BMP384_CMD_ADDR, BMP384_CMD_SOFT_RESET);
	if (status != HAL_OK) {
		hbmp->state = BMP_STATE_ERROR;
		return TELEM_ERR;
	}

	// Wait for reset completion (2ms typical)
	HAL_Delay(5);


	// Step 4: Wait for sensor ready
	timeout = 1000;
	do {
		status = BMP_ReadReg(hbmp, BMP384_STATUS_ADDR, &reg_data);
		if (status != HAL_OK) return TELEM_ERR;
		if (reg_data & BMP384_STATUS_CMD_RDY) break;
		HAL_Delay(1);
	} while (--timeout);

	if (timeout == 0) return TELEM_ERR;

	// Step 5: Configure oversampling (16x for both temp and pressure)
	reg_data = (BMP384_OVERSAMPLING_16X << BMP384_OSR_PRESS_Pos) |
	          (BMP384_OVERSAMPLING_16X << BMP384_OSR_TEMP_Pos);
	status = BMP_WriteReg(hbmp, BMP384_OSR_ADDR, reg_data);
	if (status != HAL_OK) return TELEM_ERR;

	// Step 6: Configure ODR (200Hz)
	status = BMP_WriteReg(hbmp, BMP384_ODR_ADDR, BMP384_ODR_200_HZ);
	if (status != HAL_OK) return TELEM_ERR;

	// Step 7: Configure IIR filter (coefficient 15)
	status = BMP_WriteReg(hbmp, BMP384_CONFIG_ADDR, BMP384_IIR_FILTER_COEFF_15);
	if (status != HAL_OK) return TELEM_ERR;

	// Step 8: Clear FIFO
	status = BMP_WriteReg(hbmp, BMP384_CMD_ADDR, BMP384_CMD_FIFO_FLUSH);
	if (status != HAL_OK) return TELEM_ERR;
	HAL_Delay(1);

	// Step 9: Configure FIFO watermark (50 bytes)
	status = BMP_WriteReg(hbmp, BMP384_FIFO_WTM_0_ADDR, 50);
	if (status != HAL_OK) return TELEM_ERR;
	status = BMP_WriteReg(hbmp, BMP384_FIFO_WTM_1_ADDR, 0);
	if (status != HAL_OK) return TELEM_ERR;

	// Step 10: Configure FIFO (enable pressure, temperature and time)
	reg_data = 0;
	SET_BIT(reg_data, BMP384_FIFO_MODE);	// FIFO mode enable
	SET_BIT(reg_data, BMP384_FIFO_TEMP_EN | BMP384_FIFO_PRESS_EN | BMP384_FIFO_TIME_EN);

	status = BMP_WriteReg(hbmp, BMP384_FIFO_CONFIG_1_ADDR, reg_data);
	if (status != HAL_OK) return TELEM_ERR;

	// Step 11: Configure interrupts (enable FIFO watermark interrupt)
	reg_data = 0;
	SET_BIT(reg_data, BMP384_INT_FWTM_EN);		// enable FIFO high watermark interrupt
	CLEAR_BIT(reg_data, BMP384_INT_OD);			// push-pull output
	status = BMP_WriteReg(hbmp, BMP384_INT_CTRL_ADDR, reg_data);
	if (status != HAL_OK) return TELEM_ERR;

	// Step 12: Enable sensor and set normal mode
	reg_data = 0;
	SET_BIT(reg_data, BMP384_PWR_CTRL_PRESS_EN | BMP384_PWR_CTRL_TEMP_EN);
	reg_data = (BMP384_MODE_NORMAL << BMP384_PWR_CTRL_MODE_Pos);
	status = BMP_WriteReg(hbmp, BMP384_PWR_CTRL_ADDR, reg_data);
	if (status != HAL_OK) return TELEM_ERR;

	hbmp->state = BMP_STATE_READY;

	return TELEM_OK;
}