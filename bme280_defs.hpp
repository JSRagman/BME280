/*
 * bme280_defs.hpp
 *
 *  Created on: Sep 14, 2018
 *      Author: JSRagman
 *
 *  Description:
 *    Definitions for use with the Bosch BME280 combined humidity
 *    and pressure sensor.
 *
 *    These definitions are derived from the bme280_defs.h header which
 *    is available at https://github.com/BoschSensortec/BME280_driver
 */

#ifndef BME280_DEFS_HPP_
#define BME280_DEFS_HPP_


// Chip Properties
#define BME280_ID            0x60  // chip id value
#define BME280_I2C0          0x76  // I2C address 0
#define BME280_I2C1          0x77  // I2C address 1


// BME280 Register Addresses
// --------------------------------------
#define BME280_R_ID          0xD0  // id         register address
#define BME280_R_RESET       0xE0  // reset
#define BME280_R_CTRL_HUM    0xF2  // ctrl_hum
#define BME280_R_STAT        0xF3  // status
#define BME280_R_CTRL_MEA    0xF4  // ctrl_meas
#define BME280_R_CONF        0xF5  // config

#define BME280_R_PMSB        0xF7  // pressure    msb address
#define BME280_R_PLSB        0xF8
#define BME280_R_PXLSB       0xF9

#define BME280_R_TMSB        0xFA  // temperature msb address
#define BME280_R_TLSB        0xFB
#define BME280_R_TXLSB       0xFC

#define BME280_R_HMSB        0xFD  // humidity    msb address
#define BME280_R_HLSB        0xFE


// PTH Data Registers, Indexed
#define BME280_DATA_START    0xF7
#define BME280_DATA_SIZE        8

#define BME280_PMSB_NDX         0
#define BME280_PLSB_NDX         1
#define BME280_PXLSB_NDX        2

#define BME280_TMSB_NDX         3
#define BME280_TLSB_NDX         4
#define BME280_TXLSB_NDX        5

#define BME280_HMSB_NDX         6
#define BME280_HLSB_NDX         7



// Calibration Register Addresses (Temperature and Pressure)
// ---------------------------------------------------------
#define BME280_R_CAL_T1L     0x88
#define BME280_R_CAL_T1H     0x89
#define BME280_R_CAL_T2L     0x8A
#define BME280_R_CAL_T2H     0x8B
#define BME280_R_CAL_T3L     0x8C
#define BME280_R_CAL_T3H     0x8D
#define BME280_R_CAL_P1L     0x8E
#define BME280_R_CAL_P1H     0x8F
#define BME280_R_CAL_P2L     0x90
#define BME280_R_CAL_P2H     0x91
#define BME280_R_CAL_P3L     0x92
#define BME280_R_CAL_P3H     0x93
#define BME280_R_CAL_P4L     0x94
#define BME280_R_CAL_P4H     0x95
#define BME280_R_CAL_P5L     0x96
#define BME280_R_CAL_P5H     0x97
#define BME280_R_CAL_P6L     0x98
#define BME280_R_CAL_P6H     0x99
#define BME280_R_CAL_P7L     0x9A
#define BME280_R_CAL_P7H     0x9B
#define BME280_R_CAL_P8L     0x9C
#define BME280_R_CAL_P8H     0x9D
#define BME280_R_CAL_P9L     0x9E
#define BME280_R_CAL_P9H     0x9F
#define BME280_R_CAL_H1      0xA1

// Humidity Calibration Register Addresses
// ---------------------------------------
#define BME280_R_CAL_H2L     0xE1
#define BME280_R_CAL_H2H     0xE2
#define BME280_R_CAL_H3      0xE3
#define BME280_R_CAL_H4H     0xE4
#define BME280_R_CAL_H4L     0xE5
#define BME280_R_CAL_H5L     0xE5
#define BME280_R_CAL_H5H     0xE6
#define BME280_R_CAL_H6      0xE7


// Temperature and Pressure Calibration Registers, Indexed
#define BME280_TPCAL_START   0x88
#define BME280_TPCAL_SIZE      26

#define	BME280_CAL_T1L_NDX      0
#define	BME280_CAL_T1H_NDX      1
#define	BME280_CAL_T2L_NDX      2
#define	BME280_CAL_T2H_NDX      3
#define	BME280_CAL_T3L_NDX      4
#define	BME280_CAL_T3H_NDX      5
#define	BME280_CAL_P1L_NDX      6
#define	BME280_CAL_P1H_NDX      7
#define	BME280_CAL_P2L_NDX      8
#define	BME280_CAL_P2H_NDX      9
#define	BME280_CAL_P3L_NDX     10
#define	BME280_CAL_P3H_NDX     11
#define	BME280_CAL_P4L_NDX     12
#define	BME280_CAL_P4H_NDX     13
#define	BME280_CAL_P5L_NDX     14
#define	BME280_CAL_P5H_NDX     15
#define	BME280_CAL_P6L_NDX     16
#define	BME280_CAL_P6H_NDX     17
#define	BME280_CAL_P7L_NDX     18
#define	BME280_CAL_P7H_NDX     19
#define	BME280_CAL_P8L_NDX     20
#define	BME280_CAL_P8H_NDX     21
#define	BME280_CAL_P9L_NDX     22
#define	BME280_CAL_P9H_NDX     23
#define BME280_CAL_H1_NDX      25


// Humidity Calibration Registers, Indexed
#define BME280_HUCAL_START   0xE1
#define BME280_HUCAL_SIZE       7

#define BME280_CAL_H2L_NDX      0
#define BME280_CAL_H2H_NDX      1
#define BME280_CAL_H3_NDX       2
#define BME280_CAL_H4L_NDX      4
#define BME280_CAL_H4H_NDX      3
#define BME280_CAL_H5L_NDX      4
#define BME280_CAL_H5H_NDX      5
#define BME280_CAL_H6_NDX       6



// Configuration Settings, by Register
// ------------------------------------------------------------

// ctrl_hum Register (0xF2)
// -------------------------------
// Humidity Oversampling                osrs_h
#define BME280_OSRS_H_MSK    0x07    // 00000_111  mask
#define BME280_OSRS_H_SKIP   0x00
#define BME280_OSRS_H_1X     0x01
#define BME280_OSRS_H_2X     0x02
#define BME280_OSRS_H_4X     0x03
#define BME280_OSRS_H_8X     0x04
#define BME280_OSRS_H_16X    0x05


// ctrl_meas Register (0xF4)
// -------------------------------
// Temperature Oversampling             osrs_t
#define BME280_OSRS_T_MSK    0xE0    // 111_000_00  mask
#define BME280_OSRS_T_SKIP   0x00
#define BME280_OSRS_T_1X     0x20
#define BME280_OSRS_T_2X     0x40
#define BME280_OSRS_T_4X     0x60
#define BME280_OSRS_T_8X     0x80
#define BME280_OSRS_T_16X    0xA0

// Pressure Oversampling                osrs_p
#define BME280_OSRS_P_MSK    0x1C    // 000_111_00  mask
#define BME280_OSRS_P_SKIP   0x00
#define BME280_OSRS_P_1X     0x04
#define BME280_OSRS_P_2X     0x08
#define BME280_OSRS_P_4X     0x0C
#define BME280_OSRS_P_8X     0x10
#define BME280_OSRS_P_16X    0x14

// Power Mode                           mode
#define BME280_MODE_MSK      0x03    // 000_000_11  mask
#define BME280_MODE_MSK_OUT  0xFC    // 111_111_00  mask out mode bits
#define BME280_MODE_SLEEP    0x00
#define BME280_MODE_FORCED   0x01
#define BME280_MODE_NORMAL   0x03



// config Register (0xF5)
// -------------------------------
// Inactive Duration (Normal mode)      t_sb
#define BME280_T_SB_MSK      0xE0    // 111_000_00  mask
#define BME280_T_SB_0_5      0x00    //    0.5 ms
#define BME280_T_SB_62_5     0x20    //   62.5 ms
#define BME280_T_SB_125      0x40    //  125   ms
#define BME280_T_SB_250      0x60    //  250   ms
#define BME280_T_SB_500      0x80    //  500   ms
#define BME280_T_SB_1K       0xA0    // 1000   ms
#define BME280_T_SB_10       0xC0    //   10   ms
#define BME280_T_SB_20       0xE0    //   20   ms

// IIR Filter Coefficient               filter
#define BME280_FILTER_MSK    0x1C    // 000_111_00  mask
#define BME280_FILTER_OFF    0x00
#define BME280_FILTER_2      0x04
#define BME280_FILTER_4      0x08
#define BME280_FILTER_8      0x0C
#define BME280_FILTER_16     0x10

// SPI 3-Wire Interface Enable          spi3w_en
#define BME280_SPI3W_MSK     0x01    // 000_000_01  mask
#define BME280_SPI3W_DIS     0x00
#define BME280_SPI3W_EN      0x01


// Status Register (0xF3) Mask
#define BME280_STATUS_MSK    0x09  // 0000_1001

// Reset
#define BME280_CMD_RESET     0xB6  // Reset command.
#define BME280_RESET_DELAY      3  // Reset delay, in milliseconds.
#define BME280_CONFIG_DELAY    43  // Configuration delay, in milliseconds.








































#endif /* BME280_DEFS_HPP_ */
