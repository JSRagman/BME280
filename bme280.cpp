```
/*
 * bme280.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: JSRagman
 *
 *  Description:
 *    BME280 Combined Humidity and Pressure Sensor.
 *
 *  Note:
 *    This driver assumes that device configuration will be
 *    set at startup and only the power mode is subject to change
 *    afterward.
 *
 *    Settings for the ctrl_meas, ctrl_hum, and config registers
 *    are defined below. A call to SetConfig() loads these pre-
 *    defined values.
 *
 *    bme280_defs.hpp contains additional definitions that can be
 *    used to modify these settings.
 */


#include <chrono>            // std::chrono::seconds
#include <stdint.h>          // int16_t, uint16_t
#include <thread>            // this_thread

#include "bbb-i2c.hpp"       // I2CBus
#include "bme280.hpp"


using namespace std;
using namespace std::chrono;

using namespace bbbi2c;



// Device Configuration
// --------------------------------
// Weather Monitoring Configuration
//   * From BME280 Data Sheet
//     BST-BME280-DS002-13, Rev 1.5
//     May 2018
#define BME280_CTRL_MEA_SET  BME280_OSRS_T_1X | BME280_OSRS_P_1X | BME280_MODE_SLEEP
#define BME280_CTRL_HUM_SET  BME280_OSRS_H_1X
#define BME280_CONF_SET      BME280_T_SB_1K   | BME280_FILTER_OFF



namespace bosch_bme280
{

// BME280 Constructor, Destructor
// -----------------------------------------------------------------

/*
 * BME280::BME280(I2CBus* bus, uint8_t addr)
 *
 * Description:
 *   Constructor. Assigns the I2C bus and the target device address.
 *   Initializes chip id to zero.
 *
 * Parameters:
 *   bus  - pointer to an I2CBus object
 *   addr - I2C address of the target device
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280.hpp
 */
BME280::BME280(I2CBus* bus, uint8_t addr)
{
    chipid  = 0;
    i2cbus  = bus;
    i2caddr = addr;
}

/*
 * BME280::~BME280()
 *
 * Description:
 *   Destructor. Move along. Nothing to see here.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280.hpp
 */
BME280::~BME280()
{ }



// BME280 Protected
// -----------------------------------------------------------------

/*
 * void BME280::GetRegs(uint8_t regaddr, uint8_t* data, int len)
 *
 * Description:
 *   Reads the contents of one or more consecutive device registers.
 *
 * Parameters:
 *   regaddr  - address of the first register to be read
 *   data     - pointer to a buffer that will receive data
 *   len      - the number of bytes to read
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
void BME280::GetRegs(uint8_t regaddr, uint8_t* data, int len)
{
    i2cbus->Xfer(&regaddr, 1, data, len, i2caddr);
}

/*
 * void BME280::SetRegs(uint8_t* data, int len)
 *
 * Description:
 *   Writes to one or more device registers. Outgoing bytes must
 *   be organized in pairs - a register address followed by a data
 *   byte for that register.
 *
 *   This {address, data} sequence is repeated for each register
 *   to be written.
 *
 * Parameters:
 *   data - pointer to a buffer that contains data which will be
 *          written to the device
 *   len  - the total number of bytes to be written
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
void BME280::SetRegs(uint8_t* data, int len)
{
    i2cbus->Write(data, len, i2caddr);
}



// BME280 Public
// -----------------------------------------------------------------

/*
 * void BME280::LoadCalParams()
 *
 * Description:
 *   Loads calibration parameters from the device ROM.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
void BME280::LoadCalParams()
{
    uint8_t tpcparams[BME280_TPCAL_SIZE] {0};
    uint8_t hucparams[BME280_HUCAL_SIZE] {0};

    this->GetRegs(BME280_TPCAL_START, tpcparams, BME280_TPCAL_SIZE);
    this->GetRegs(BME280_HUCAL_START, hucparams, BME280_HUCAL_SIZE);

    cparams.t1 =          (((uint16_t)tpcparams[1] << 8) | (uint16_t)tpcparams[0]);
    cparams.t2 = (int16_t)(((uint16_t)tpcparams[3] << 8) | (uint16_t)tpcparams[2]);
    cparams.t3 = (int16_t)(((uint16_t)tpcparams[5] << 8) | (uint16_t)tpcparams[4]);

    cparams.p1 =          (((uint16_t)tpcparams[7]  << 8) | (uint16_t)tpcparams[6]);
    cparams.p2 = (int16_t)(((uint16_t)tpcparams[9]  << 8) | (uint16_t)tpcparams[8]);
    cparams.p3 = (int16_t)(((uint16_t)tpcparams[11] << 8) | (uint16_t)tpcparams[10]);
    cparams.p4 = (int16_t)(((uint16_t)tpcparams[13] << 8) | (uint16_t)tpcparams[12]);
    cparams.p5 = (int16_t)(((uint16_t)tpcparams[15] << 8) | (uint16_t)tpcparams[14]);
    cparams.p6 = (int16_t)(((uint16_t)tpcparams[17] << 8) | (uint16_t)tpcparams[16]);
    cparams.p7 = (int16_t)(((uint16_t)tpcparams[19] << 8) | (uint16_t)tpcparams[18]);
    cparams.p8 = (int16_t)(((uint16_t)tpcparams[21] << 8) | (uint16_t)tpcparams[20]);
    cparams.p9 = (int16_t)(((uint16_t)tpcparams[23] << 8) | (uint16_t)tpcparams[22]);

    cparams.h1 = tpcparams[25];

    cparams.h2 = (int16_t)(((uint16_t)hucparams[1] << 8) | (uint16_t)hucparams[0]);
    cparams.h3 = hucparams[2];

    int16_t h4_msb = (int16_t)(int8_t)hucparams[3] * 16;
    int16_t h4_lsb = (int16_t)(hucparams[4] & 0x0F);
    cparams.h4 = h4_msb | h4_lsb;

    int16_t h5_msb = (int16_t)(int8_t)hucparams[5] * 16;
    int16_t h5_lsb = (int16_t)(hucparams[4] >> 4);
    cparams.h5 = h5_msb | h5_lsb;

    cparams.h6 = (int8_t)hucparams[6];

    cparams.loaded = true;
}

/*
 * TPH32SensorData BME280::GetSensorData()
 *
 * Description:
 *   Retrieves raw temperature, pressure, and humidity data
 *   from the sensor.
 *
 * Returns:
 *   Returns a structure containing uncompensated temperature,
 *   pressure, and humidity data, along with a time stamp.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
TPH32SensorData BME280::GetSensorData()
{
TPH32SensorData sensdat;
uint8_t regdat[BME280_DATA_SIZE] {0};

this->GetRegs(BME280_DATA_START, regdat, BME280_DATA_SIZE);

    sensdat.pressure = (
            ((uint32_t)regdat[BME280_PMSB_NDX]  << 12) |
            ((uint32_t)regdat[BME280_PLSB_NDX]  <<  4) |
            ((uint32_t)regdat[BME280_PXLSB_NDX] >>  4)
            );

    sensdat.temperature = (
            ((uint32_t)regdat[BME280_TMSB_NDX]  << 12) |
            ((uint32_t)regdat[BME280_TLSB_NDX]  <<  4) |
            ((uint32_t)regdat[BME280_TXLSB_NDX] >>  4)
            );

    sensdat.humidity = (
            ((uint32_t)regdat[BME280_HMSB_NDX]  <<  8) |
             (uint32_t)regdat[BME280_HLSB_NDX]
            );

    return sensdat;
}

/*
 * TPH32CompData BME280::GetComp32FixedData()
 *
 * Description:
 *   Retrieves a temperature, pressure, and humidity reading and applies
 *   32-bit fixed-point compensation.
 *
 *   Temperature compensation is performed first, in order to generate
 *   the 32-bit integer (tfine) that is required for pressure and
 *   humidity compensation.
 *
 * Returns:
 *   Returns a TPH32CompData structure containing a time stamp, a
 *   temperature reading (in 1/100 degrees centigrade), a pressure
 *   reading (in pascals), and a humidity reading, which can be
 *   devided by 1024 to give percent relative humidity.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
TPH32CompData BME280::GetComp32FixedData()
{
    TPH32CompData   compdat;
    TPH32SensorData sensdat = this->GetSensorData();

    compdat.timestamp   = sensdat.timestamp;
    compdat.temperature = this->Comp32FixedTemp(sensdat.temperature);
    compdat.pressure    = this->Comp32FixedPress(sensdat.pressure);
    compdat.humidity    = this->Comp32FixedHumid(sensdat.humidity);

    return compdat;
}

/*
 * TPHDoubleCompData BME280::GetCompDoubleData()
 *
 * Description:
 *   Retrieves a temperature, pressure, and humidity reading and applies
 *   double floating-point compensation.
 *
 *   Temperature compensation is performed first, in order to generate
 *   the 32-bit integer (tfine) that is required for pressure and
 *   humidity compensation.
 *
 * Returns:
 *   Returns a TPHDoubleCompData structure containing a time stamp, a
 *   temperature reading (in degrees centigrade), a pressure reading (in
 *   pascals), and a humidity reading (in percent relative humidity).
 */
TPHDoubleCompData BME280::GetCompDoubleData()
{
    TPHDoubleCompData compdat;
    TPH32SensorData   sensdat = this->GetSensorData();

    compdat.timestamp   = sensdat.timestamp;
    compdat.temperature = this->CompDoubleTemp(sensdat.temperature);
    compdat.pressure    = this->CompDoublePress(sensdat.pressure);
    compdat.humidity    = this->CompDoubleHumid(sensdat.humidity);

    return compdat;
}

/*
 * void BME280::SetConfig()
 *
 * Description:
 *   Loads pre-defined configuration settings. Returns after
 *   a time delay.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
void BME280::SetConfig()
{
    uint8_t configdat[6];
    configdat[0] = BME280_R_CTRL_HUM;
    configdat[1] = BME280_CTRL_HUM_SET;
    configdat[2] = BME280_R_CONF;
    configdat[3] = BME280_CONF_SET;
    configdat[4] = BME280_R_CTRL_MEA;
    configdat[5] = BME280_CTRL_MEA_SET;

    this->SetRegs(configdat, 6);
    this_thread::sleep_for(milliseconds(BME280_CONFIG_DELAY));
}

/*
 * void BME280::Force()
 *
 * Description:
 *   Manually initiates a measurement cycle.
 *
 * Initial Conditions:
 *   All other configuration settings must be completed before
 *   calling this function.
 *
 *   The sensor must be in sleep mode.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280.hpp
 */
void BME280::Force()
{
    uint8_t ctrl;
    this->GetRegs(BME280_R_CTRL_MEA, &ctrl, 1);

    uint8_t dat[] { BME280_R_CTRL_MEA, (uint8_t)(ctrl | BME280_MODE_FORCED) };
    this->SetRegs(dat, 2);
}

/*
 * void BME280::Reset(bool reload)
 *
 * Description:
 *   Resets the device. Allows time for the reset process to
 *   complete before returning. Optionally, reloads device
 *   configuration when reset is complete.
 *
 * Parameters:
 *   reload - Optional. If true, reloads configuration settings
 *            following the reset.
 *            Default value is false.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280.hpp
 */
void BME280::Reset(bool reload)
{
    uint8_t dat[] { BME280_R_RESET, BME280_CMD_RESET };
    this->SetRegs(dat, 2);

    this_thread::sleep_for(milliseconds(BME280_RESET_DELAY));

    if (reload)
        this->SetConfig();
}

/*
 * void BME280::Sleep()
 *
 * Description:
 *   Places the device in sleep mode by setting the ctrl_meas
 *   register mode bits to zero.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
void BME280::Sleep()
{
    uint8_t ctrl;
    this->GetRegs(BME280_R_CTRL_MEA, &ctrl, 1);

    uint8_t dat[] { BME280_R_CTRL_MEA, (uint8_t)(ctrl & BME280_MODE_MSK_OUT) };
    this->SetRegs(dat, 2);
}

} // namespace bosch_bme280
```
