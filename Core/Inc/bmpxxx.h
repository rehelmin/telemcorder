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
#define BMP384_ERR_FATAL             (1 << 0)  // Fatal error
#define BMP384_ERR_CMD               (1 << 1)  // Command execution error
#define BMP384_ERR_CONF              (1 << 2)  // Configuration error

// Status Register
#define BMP384_STATUS_ADDR           0x03  // Data ready status
#define BMP384_STATUS_CMD_RDY        (1 << 4)  // Command ready
#define BMP384_STATUS_DRDY_PRESS     (1 << 5)  // Pressure data ready
#define BMP384_STATUS_DRDY_TEMP      (1 << 6)  // Temperature data ready

// Pressure and Temperature Data Registers
#define BMP384_DATA_0_ADDR           0x04  // press_7_0
#define BMP384_DATA_1_ADDR           0x05  // press_15_8
#define BMP384_DATA_2_ADDR           0x06  // press_23_16
#define BMP384_DATA_3_ADDR           0x07  // temp_7_0
#define BMP384_DATA_4_ADDR           0x08  // temp_15_8
#define BMP384_DATA_5_ADDR           0x09  // temp_23_16

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
#define BMP384_INT_STATUS_FIFO_FULL  (1 << 0)  // FIFO full interrupt
#define BMP384_INT_STATUS_FIFO_WTM   (1 << 1)  // FIFO watermark interrupt
#define BMP384_INT_STATUS_DRDY       (1 << 3)  // Data ready interrupt

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
#define BMP384_FIFO_MODE_POS         0
#define BMP384_FIFO_MODE_MSK         (0x03 << BMP384_FIFO_MODE_POS)
#define BMP384_FIFO_STOP_ON_FULL_POS 1
#define BMP384_FIFO_STOP_ON_FULL_MSK (0x01 << BMP384_FIFO_STOP_ON_FULL_POS)
#define BMP384_FIFO_TIME_EN_POS      2
#define BMP384_FIFO_TIME_EN_MSK      (0x01 << BMP384_FIFO_TIME_EN_POS)
#define BMP384_FIFO_PRESS_EN_POS     3
#define BMP384_FIFO_PRESS_EN_MSK     (0x01 << BMP384_FIFO_PRESS_EN_POS)
#define BMP384_FIFO_TEMP_EN_POS      4
#define BMP384_FIFO_TEMP_EN_MSK      (0x01 << BMP384_FIFO_TEMP_EN_POS)
#define BMP384_FIFO_SUBSAMP_POS      5
#define BMP384_FIFO_SUBSAMP_MSK      (0x07 << BMP384_FIFO_SUBSAMP_POS)
#define BMP384_FIFO_DATA_SELECT_POS  0
#define BMP384_FIFO_DATA_SELECT_MSK  (0x03 << BMP384_FIFO_DATA_SELECT_POS)

// FIFO Configuration 2
#define BMP384_FIFO_CONFIG_2_ADDR    0x18
#define BMP384_FIFO_WTM_POS          0
#define BMP384_FIFO_WTM_MSK          (0x03FF << BMP384_FIFO_WTM_POS)

// Interrupt Control
#define BMP384_INT_CTRL_ADDR         0x19
#define BMP384_INT_EN_POS            0
#define BMP384_INT_EN_MSK            (0x01 << BMP384_INT_EN_POS)
#define BMP384_INT_LATCH_POS         1
#define BMP384_INT_LATCH_MSK         (0x01 << BMP384_INT_LATCH_POS)
#define BMP384_INT_LEVEL_POS         2
#define BMP384_INT_LEVEL_MSK         (0x01 << BMP384_INT_LEVEL_POS)
#define BMP384_INT_OD_POS            3
#define BMP384_INT_OD_MSK            (0x01 << BMP384_INT_OD_POS)
#define BMP384_INT_FWM_EN_POS        5
#define BMP384_INT_FWM_EN_MSK        (0x01 << BMP384_INT_FWM_EN_POS)
#define BMP384_INT_FFULL_EN_POS      6
#define BMP384_INT_FFULL_EN_MSK      (0x01 << BMP384_INT_FFULL_EN_POS)
#define BMP384_INT_DRDY_EN_POS      7
#define BMP384_INT_DRDY_EN_MSK       (0x01 << BMP384_INT_DRDY_EN_POS)

// Interface Configuration
#define BMP384_IF_CONF_ADDR          0x1A
#define BMP384_IF_CONF_SPI3_POS      0
#define BMP384_IF_CONF_SPI3_MSK      (0x01 << BMP384_IF_CONF_SPI3_POS)

// Power Control
#define BMP384_PWR_CTRL_ADDR         0x1B
#define BMP384_PWR_CTRL_PRESS_EN_POS 0
#define BMP384_PWR_CTRL_PRESS_EN_MSK (0x01 << BMP384_PWR_CTRL_PRESS_EN_POS)
#define BMP384_PWR_CTRL_TEMP_EN_POS  1
#define BMP384_PWR_CTRL_TEMP_EN_MSK  (0x01 << BMP384_PWR_CTRL_TEMP_EN_POS)
#define BMP384_PWR_CTRL_MODE_POS     4
#define BMP384_PWR_CTRL_MODE_MSK     (0x03 << BMP384_PWR_CTRL_MODE_POS)

// Oversampling Configuration
#define BMP384_OSR_ADDR              0x1C
#define BMP384_OSR_TEMP_POS          0
#define BMP384_OSR_TEMP_MSK          (0x07 << BMP384_OSR_TEMP_POS)
#define BMP384_OSR_PRESS_POS         3
#define BMP384_OSR_PRESS_MSK         (0x07 << BMP384_OSR_PRESS_POS)

// Output Data Rate
#define BMP384_ODR_ADDR              0x1D
#define BMP384_ODR_POS               0
#define BMP384_ODR_MSK               (0x07 << BMP384_ODR_POS)

// Configuration Register
#define BMP384_CONFIG_ADDR           0x1F
#define BMP384_CONFIG_IIR_FILTER_POS 0
#define BMP384_CONFIG_IIR_FILTER_MSK (0x07 << BMP384_CONFIG_IIR_FILTER_POS)

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

/**
 * @brief Initialize the communication interface to the BMP sensor.
 * param @hspi A handle to the SPI peripheral.
*/
int BMP_Init(SPI_HandleTypeDef *hspi);




#ifdef __cplusplus
}
#endif

#endif /* __BMP_H */