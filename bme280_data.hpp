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
#include <deque>             // deque
#include <mutex>             // mutex
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


// 32-bit fixed-point
// -------------------------------------------------

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
 * struct TPH32Summary
 *
 * Description:
 *   Summarize a set of temperature, pressure, or
 *   humidity readings.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280_data.hpp
 */
struct TPH32Summary
{
    time_t   timestart;
    time_t   timestop;
    int      samplecount;

    int32_t high;
    int32_t low;
    double  average;
};

/*
 * class TPH32DataQueue
 *
 * Description:
 *   Accumulates compensated temperature, pressure, and humidity
 *   readings.
 */
class TPH32DataQueue
{
  protected:
    std::deque<TPH32CompData> dq;
    unsigned int qcap;

    int32_t t_high, t_low;
    int32_t p_high, p_low;
    int32_t h_high, h_low;

    double t_avg, p_avg, h_avg;
    bool   stale;

  public:
    std::mutex mtx;

    TPH32DataQueue ( unsigned int capacity=60 );

    TPH32CompData back  ();
    TPH32CompData front ();
    TPH32CompData pop   ();

    void  push   ( TPH32CompData data );
    void  resize ( int newcapacity );

    int   capacity ();
    void  clear ();
    bool  full  ();
    int   size  ();
    void  summarize ();

    time_t   timestart ();
    time_t   timestop  ();

    int32_t  temperature_high();
    int32_t  temperature_low();
    double   temperature_average();

    int32_t  pressure_high();
    int32_t  pressure_low();
    double   pressure_average();

    int32_t  humidity_high();
    int32_t  humidity_low();
    double   humidity_average();
};



// double
// -------------------------------------------------

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

/*
 * struct TPHDoubleSummary
 *
 * Description:
 *   Summarize a set of temperature, pressure, or
 *   humidity readings.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s):
 *   bme280_data.hpp
 */
struct TPHDoubleSummary
{
    time_t   timestart;
    time_t   timestop;
    int      samplecount;

    double  high;
    double  low;
    double  average;
};

/*
 * class TPHDoubleDataQueue
 *
 * Description:
 *   Accumulates compensated temperature, pressure, and humidity
 *   readings.
 */
class TPHDoubleDataQueue
{
  protected:
    std::deque<TPHDoubleCompData> dq;
    unsigned int qcap;

    double t_high, t_low;
    double p_high, p_low;
    double h_high, h_low;

    double t_avg, p_avg, h_avg;
    bool   stale;

  public:
    std::mutex mtx;

    TPHDoubleDataQueue ( unsigned int capacity=60 );

    TPHDoubleCompData back  ();
    TPHDoubleCompData front ();
    TPHDoubleCompData pop   ();

    void  push   ( TPHDoubleCompData data );
    void  resize ( int newcapacity );

    int   capacity ();
    void  clear ();
    bool  full  ();
    int   size  ();
    void  summarize ();

    time_t   timestart ();
    time_t   timestop  ();

    double  temperature_high();
    double  temperature_low();
    double  temperature_average();

    double  pressure_high();
    double  pressure_low();
    double  pressure_average();

    double  humidity_high();
    double  humidity_low();
    double  humidity_average();
};

} // namespace bosch_bme280

#endif /* BME280_DATA_HPP_ */
```
