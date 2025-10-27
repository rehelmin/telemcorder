#ifndef __BMP_H
#define __BMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

// BMP384 Register Defines & Bit Masks
// Bosch Sensortec BMP384 Pressure Sensor Register Map

// Chip ID
#define BMP384_CHIP_ID_ADDR          0x00  // Fixed value: 0x50

// Error Register
#define BMP384_ERR_REG_ADDR          0x02  // Error flags
#define BMP384_ERR_FATAL             (0x01 << 0)  // Fatal error
#define BMP384_ERR_CMD               (0x01 << 1)  // Command execution error
#define BMP384_ERR_CONF              (0x01 << 2)  // Configuration error

// Status Register
#define BMP384_STATUS_ADDR           0x03  // Data ready status
#define BMP384_STATUS_CMD_RDY        (0x01 << 4)  // Command ready
#define BMP384_STATUS_DRDY_PRESS     (0x01 << 5)  // Pressure data ready
#define BMP384_STATUS_DRDY_TEMP      (0x01 << 6)  // Temperature data ready

// Pressure and Temperature Data Registers
#define BMP384_DATA_0_ADDR           0x04  // press_xlsb_7_0
#define BMP384_DATA_1_ADDR           0x05  // press_lsb_15_8
#define BMP384_DATA_2_ADDR           0x06  // press_msb_23_16
#define BMP384_DATA_3_ADDR           0x07  // temp_xlsb_7_0
#define BMP384_DATA_4_ADDR           0x08  // temp_lsb_15_8
#define BMP384_DATA_5_ADDR           0x09  // temp_msb_23_16

// Sensor Time Registers
#define BMP384_SENSORTIME_0_ADDR     0x0C  // sensor_time_7_0
#define BMP384_SENSORTIME_1_ADDR     0x0D  // sensor_time_15_8
#define BMP384_SENSORTIME_2_ADDR     0x0E  // sensor_time_23_16
#define BMP384_SENSORTIME_3_ADDR     0x0F  // sensor_time_31_24

// Event Register
#define BMP384_EVENT_ADDR             0x10  // Power-on reset detect
#define BMP384_EVENT_POR_DETECTED    (1 << 0)  // Power-on reset detected

// Interrupt Status
#define BMP384_INT_STATUS_ADDR       0x11  // Interrupt status flags
#define BMP384_INT_STATUS_FWM_INT    (0x01 << 0)  // FIFO watermark interrupt
#define BMP384_INT_STATUS_FFULL_INT  (0x01 << 1)  // FIFO full interrupt
#define BMP384_INT_STATUS_DRDY       (0x01 << 3)  // Data ready interrupt

// FIFO Length Registers
#define BMP384_FIFO_LENGTH_0_ADDR    0x12  // fifo_byte_counter_7_0
#define BMP384_FIFO_LENGTH_1_ADDR    0x13  // fifo_byte_counter_8

// FIFO Data Register
#define BMP384_FIFO_DATA_ADDR        0x14  // fifo_data

// FIFO Watermark Registers
#define BMP384_FIFO_WTM_0_ADDR       0x15  // fifo_water_mark_7_0
#define BMP384_FIFO_WTM_1_ADDR       0x16  // fifo_water_mark_8

// FIFO Configuration 1
#define BMP384_FIFO_CONFIG_1_ADDR    0x17
#define BMP384_FIFO_MODE_Pos         0
#define BMP384_FIFO_MODE_Msk         (0x01 << BMP384_FIFO_MODE_Pos)
#define BMP384_FIFO_MODE             BMP384_FIFO_MODE_Msk
#define BMP384_FIFO_STOP_ON_FULL_Pos 1
#define BMP384_FIFO_STOP_ON_FULL_Msk (0x01 << BMP384_FIFO_STOP_ON_FULL_Pos)
#define BMP384_FIFO_STOP_ON_FULL     BMP384_FIFO_STOP_ON_FULL_Msk
#define BMP384_FIFO_TIME_EN_Pos      2
#define BMP384_FIFO_TIME_EN_Msk      (0x01 << BMP384_FIFO_TIME_EN_Pos)
#define BMP384_FIFO_TIME_EN          BMP384_FIFO_TIME_EN_Msk
#define BMP384_FIFO_PRESS_EN_Pos     3
#define BMP384_FIFO_PRESS_EN_Msk     (0x01 << BMP384_FIFO_PRESS_EN_Pos)
#define BMP384_FIFO_PRESS_EN         BMP384_FIFO_PRESS_EN_Msk
#define BMP384_FIFO_TEMP_EN_Pos      4
#define BMP384_FIFO_TEMP_EN_Msk      (0x01 << BMP384_FIFO_TEMP_EN_Pos)
#define BMP384_FIFO_TEMP_EN          BMP384_FIFO_TEMP_EN_Msk

// FIFO Configuration 2
#define BMP384_FIFO_CONFIG_2_ADDR    0x18
#define BMP384_FIFO_SUBSAMP_Pos      0
#define BMP384_FIFO_SUBSAMP_Msk      (0x07 << BMP384_FIFO_SUBSAMP_Pos)
#define BMP384_FIFO_SUBSAMP          BMP384_FIFO_SUBSAMP_Msk
#define BMP384_FIFO_DATA_SELECT_Pos  3
#define BMP384_FIFO_DATA_SELECT_Msk  (0x03 << BMP384_FIFO_DATA_SELECT_Pos)
#define BMP384_FIFO_DATA_SELECT      BMP384_FIFO_DATA_SELECT_Msk

// Interrupt Control
#define BMP384_INT_CTRL_ADDR         0x19
#define BMP384_INT_OD_Pos            0
#define BMP384_INT_OD_Msk            (0x01 << BMP384_INT_OD_Pos)
#define BMP384_INT_OD                BMP384_INT_OD_Msk
#define BMP384_INT_LEVEL_Pos         1
#define BMP384_INT_LEVEL_Msk         (0x01 << BMP384_INT_LEVEL_Pos)
#define BMP384_INT_LEVEL             BMP384_INT_LEVEL_Msk
#define BMP384_INT_LATCH_Pos         2
#define BMP384_INT_LATCH_Msk         (0x01 << BMP384_INT_LATCH_Pos)
#define BMP384_INT_LATCH             BMP384_INT_LATCH_Msk
#define BMP384_INT_FWTM_EN_Pos       3
#define BMP384_INT_FWTM_EN_Msk       (0x01 << BMP384_INT_FWTM_EN_Pos)
#define BMP384_INT_FWTM_EN           BMP384_INT_FWTM_EN_Msk
#define BMP384_INT_FFULL_EN_Pos      4
#define BMP384_INT_FFULL_EN_Msk      (0x01 << BMP384_INT_FFULL_EN_Pos)
#define BMP384_INT_FFULL_EN          BMP384_INT_FFULL_EN_Msk
#define BMP384_INT_DRDY_EN_Pos       6
#define BMP384_INT_DRDY_EN_Msk       (0x01 << BMP384_INT_DRDY_EN_Pos)
#define BMP384_INT_DRDY_EN           BMP384_INT_DRDY_EN_Msk

// Interface Configuration
#define BMP384_IF_CONF_ADDR          0x1A
#define BMP384_IF_CONF_SPI3_Pos      0
#define BMP384_IF_CONF_SPI3_Msk      (0x01 << BMP384_IF_CONF_SPI3_Pos)
#define BMP384_IF_CONF_SPI3          BMP384_IF_CONF_SPI3_Msk

// Power Control
#define BMP384_PWR_CTRL_ADDR         0x1B
#define BMP384_PWR_CTRL_PRESS_EN_Pos 0
#define BMP384_PWR_CTRL_PRESS_EN_Msk (0x01 << BMP384_PWR_CTRL_PRESS_EN_Pos)
#define BMP384_PWR_CTRL_PRESS_EN     BMP384_PWR_CTRL_PRESS_EN_Msk
#define BMP384_PWR_CTRL_TEMP_EN_Pos  1
#define BMP384_PWR_CTRL_TEMP_EN_Msk  (0x01 << BMP384_PWR_CTRL_TEMP_EN_Pos)
#define BMP384_PWR_CTRL_TEMP_EN      BMP384_PWR_CTRL_TEMP_EN_Msk
#define BMP384_PWR_CTRL_MODE_Pos     4
#define BMP384_PWR_CTRL_MODE_Msk     (0x03 << BMP384_PWR_CTRL_MODE_Pos)
#define BMP384_PWR_CTRL_MODE         BMP384_PWR_CTRL_MODE_Msk

// Oversampling Configuration
#define BMP384_OSR_ADDR              0x1C
#define BMP384_OSR_PRESS_Pos         0
#define BMP384_OSR_PRESS_Msk         (0x07 << BMP384_OSR_PRESS_Pos)
#define BMP384_OSR_TEMP_Pos          3
#define BMP384_OSR_TEMP_Msk          (0x07 << BMP384_OSR_TEMP_Pos)

// Output Data Rate
#define BMP384_ODR_ADDR              0x1D
#define BMP384_ODR_Pos               0
#define BMP384_ODR_Msk               (0x07 << BMP384_ODR_Pos)
#define BMP384_ODR                   BMP384_ODR_Msk

// Configuration Register
#define BMP384_CONFIG_ADDR           0x1F
#define BMP384_CONFIG_IIR_FILTER_Pos 1
#define BMP384_CONFIG_IIR_FILTER_Msk (0x07 << BMP384_CONFIG_IIR_FILTER_Pos)

// Command Register
#define BMP384_CMD_ADDR              0x7E
#define BMP384_CMD_NOP               0x00
#define BMP384_CMD_FIFO_FLUSH        0xB0
#define BMP384_CMD_SOFT_RESET        0xB6

// Calibration Coefficient Registers (NVM)
#define BMP384_NVM_PAR_T1_ADDR       0x31  // 2 bytes, unsigned
#define BMP384_NVM_PAR_T2_ADDR       0x33  // 2 bytes, unsigned
#define BMP384_NVM_PAR_T3_ADDR       0x35  // 1 byte, signed

#define BMP384_NVM_PAR_P1_ADDR       0x36  // 2 bytes, signed
#define BMP384_NVM_PAR_P2_ADDR       0x38  // 2 bytes, signed
#define BMP384_NVM_PAR_P3_ADDR       0x3A  // 1 byte, signed
#define BMP384_NVM_PAR_P4_ADDR       0x3B  // 1 byte, signed
#define BMP384_NVM_PAR_P5_ADDR       0x3C  // 2 bytes, unsigned
#define BMP384_NVM_PAR_P6_ADDR       0x3E  // 2 bytes, unsigned
#define BMP384_NVM_PAR_P7_ADDR       0x40  // 1 byte, signed
#define BMP384_NVM_PAR_P8_ADDR       0x41  // 1 byte, signed
#define BMP384_NVM_PAR_P9_ADDR       0x42  // 2 bytes, signed
#define BMP384_NVM_PAR_P10_ADDR      0x44  // 1 byte, signed
#define BMP384_NVM_PAR_P11_ADDR      0x45  // 1 byte, signed

// Power Mode Values
#define BMP384_MODE_SLEEP            0x00
#define BMP384_MODE_FORCED           0x01
#define BMP384_MODE_NORMAL           0x03

// Oversampling Values
#define BMP384_NO_OVERSAMPLING       0x00
#define BMP384_OVERSAMPLING_2X       0x01
#define BMP384_OVERSAMPLING_4X       0x02
#define BMP384_OVERSAMPLING_8X       0x03
#define BMP384_OVERSAMPLING_16X      0x04
#define BMP384_OVERSAMPLING_32X      0x05

// ODR (Output Data Rate) Values
#define BMP384_ODR_200_HZ            0x00
#define BMP384_ODR_100_HZ            0x01
#define BMP384_ODR_50_HZ             0x02
#define BMP384_ODR_25_HZ             0x03
#define BMP384_ODR_12_5_HZ           0x04
#define BMP384_ODR_6_25_HZ           0x05
#define BMP384_ODR_3_1_HZ            0x06
#define BMP384_ODR_1_5_HZ            0x07

// IIR Filter Coefficients
#define BMP384_IIR_FILTER_BYPASS     0x00
#define BMP384_IIR_FILTER_COEFF_1    0x01
#define BMP384_IIR_FILTER_COEFF_3    0x02
#define BMP384_IIR_FILTER_COEFF_7    0x03
#define BMP384_IIR_FILTER_COEFF_15   0x04
#define BMP384_IIR_FILTER_COEFF_31   0x05
#define BMP384_IIR_FILTER_COEFF_63   0x06
#define BMP384_IIR_FILTER_COEFF_127  0x07


// Expected chip ID
#define BMP384_CHIP_ID_VALUE         0x50

/**
  * @brief BMP State structure definition
  */
typedef enum
{
  BMP_STATE_RESET      = 0x00U,    /*!< Peripheral not Initialized                         */
  BMP_STATE_READY      = 0x01U,    /*!< Peripheral Initialized and ready for use           */
  BMP_STATE_BUSY       = 0x02U,    /*!< an internal process is ongoing                     */
  BMP_STATE_ERROR      = 0x03U,    /*!< BMP error state                                    */
} BMP_StateTypeDef;

typedef struct __BMP_HandleTypeDef
{
	SPI_HandleTypeDef *hspi;
	BMP_StateTypeDef state;

} BMP_HandleTypeDef;

/**
 * @brief Initialize the communication interface to the BMP sensor.
 * 
 * @param hbmp A statically allocated handle for the BMP driver to use.
 * @param hspi A handle to the SPI peripheral.
*/
int BMP_Init(BMP_HandleTypeDef *hbmp, SPI_HandleTypeDef *hspi);

/**
 * @brief 
*/
int BMP_Rx_Process(BMP_HandleTypeDef *hbmp);




#ifdef __cplusplus
}
#endif

#endif /* __BMP_H */