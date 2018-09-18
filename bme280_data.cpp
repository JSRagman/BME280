```
/*
 * bme280_data.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: JSRagman
 *
 *  Description:
 *    Implements data structures for use with the BME280.
 */


#include <chrono>            // time()

#include "bme280_data.hpp"

using namespace std;

namespace bosch_bme280
{

/*
 * CalParams::CalParams()
 *
 * Description:
 *   Constructor. Initializes all parameters to zero,
 *   loaded = false.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280_data.hpp
 */
CalParams::CalParams()
{
    t1 = 0;
    t2 = 0;
    t3 = 0;

    tfine = 0;

    p1 = 0;
    p2 = 0;
    p3 = 0;
    p4 = 0;
    p5 = 0;
    p6 = 0;
    p7 = 0;
    p8 = 0;
    p9 = 0;

    h1 = 0;
    h2 = 0;
    h3 = 0;
    h4 = 0;
    h5 = 0;
    h6 = 0;

    loaded = false;
}

/*
 * TPH32SensorData::TPH32SensorData()
 *
 * Description:
 *   Constructor. Initializes the timestamp to the present moment.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280_data.hpp
 */
TPH32SensorData::TPH32SensorData()
{
    timestamp   = time(nullptr);
    temperature = 0;
    pressure    = 0;
    humidity    = 0;
}

/*
 * TPH32CompData::TPH32CompData()
 *
 * Description:
 *   Constructor. Initializes the timestamp to the present moment.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280_data.hpp
 */
TPH32CompData::TPH32CompData()
{
    timestamp   = time(nullptr);
    temperature = 0;
    pressure    = 0;
    humidity    = 0;
}

/*
 * TPHDoubleCompData::TPHDoubleCompData()
 *
 * Description:
 *   Constructor. Initializes the timestamp to the present moment.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280_data.hpp
 */
TPHDoubleCompData::TPHDoubleCompData()
{
    timestamp   = time(nullptr);
    temperature = 0.0;
    pressure    = 0.0;
    humidity    = 0.0;
}

} // namespace bosch_bme280
```
