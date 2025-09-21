#include "bmpxxx.h"

#define BMP_CS_LOW 	HAL_GPIO_WritePin(NBMP_CS_GPIO_Port, NBMP_CS_Pin, GPIO_PIN_RESET)
#define BMP_CS_HI 	HAL_GPIO_WritePin(NBMP_CS_GPIO_Port, NBMP_CS_Pin, GPIO_PIN_SET)

int BMP_Init(SPI_HandleTypeDef *hspi)
{

	const uint8_t READ_FLAG = 1 << 7;
	const uint8_t WRITE_FLAG = 0x0;

	HAL_StatusTypeDef status;
	uint8_t send_data[2] = {
		READ_FLAG | BMP384_CHIP_ID_ADDR,
		0xFF
	};

	// initialize the SPI mode by doing a dummy read of the CHIP_ID register
	BMP_CS_LOW;
	status = HAL_SPI_Transmit(hspi, send_data, 2, 10);
	BMP_CS_HI;

	return (status == HAL_OK) ? TELEM_OK : TELEM_ERR;
}