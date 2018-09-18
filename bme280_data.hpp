```
/*
 * bme280_data.hpp
 *
 *  Created on: Sep 14, 2018
 *      Author: JSRagman
 *
 *  Description:
 *    Data structures for use with the BME280.
 */

#ifndef BME280_DATA_HPP_
#define BME280_DATA_HPP_


#include <chrono>            // time_t
#include <stdint.h>          // uint16_t, int16_t


namespace bosch_bme280
{

/*
 * struct CalParams
 *
 * Description:
 *   A structure for BME280 calibration parameters.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280_data.hpp
 */
struct CalParams
{
    uint16_t  t1;
     int16_t  t2;
     int16_t  t3;

     int32_t  tfine;

    uint16_t  p1;
     int16_t  p2;
     int16_t  p3;
     int16_t  p4;
     int16_t  p5;
     int16_t  p6;
     int16_t  p7;
     int16_t  p8;
     int16_t  p9;

    uint8_t   h1;
     int16_t  h2;
    uint8_t   h3;
     int16_t  h4;
     int16_t  h5;
     int8_t   h6;

    bool loaded;

    CalParams();
};

/*
 * struct SensorData
 *
 * Description:
 *   A structure for BME280 uncompensated temperature, pressure,
 *   and humidity data.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280_data.hpp
 */
struct TPH32SensorData
{
    time_t  timestamp;

    uint32_t  temperature;
    uint32_t  pressure;
    uint32_t  humidity;

    TPH32SensorData ( );
};


/*
 * struct TPH32CompData
 *
 * Description:
 *   A structure for 32-bit, fixed-point compensated temperature,
 *   pressure, and humidity data.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280_data.hpp
 */
struct TPH32CompData
{
    time_t timestamp;

    int32_t temperature;
    int32_t pressure;
    int32_t humidity;

    TPH32CompData ( );
};


/*
 * struct TPHDoubleCompData
 *
 * Description:
 * Description:
 *   A structure for double floating-point compensated temperature,
 *   pressure, and humidity data.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280_data.hpp
 */
struct TPHDoubleCompData
{
    time_t timestamp;

    double temperature;
    double pressure;
    double humidity;

    TPHDoubleCompData ( );
};


} // namespace bosch_bme280

#endif /* BME280_DATA_HPP_ */
```
