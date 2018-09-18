```
/*
 * bme280.hpp
 *
 *  Created on: Sep 14, 2018
 *      Author: JSRagman
 *
 *  Description:
 *    Bosch Sensortec BME280 combined humidity and pressure sensor.
 *
 *  Note:
 *    JSRagman is not associated in any way with the good people at
 *    Bosch, although sometimes he is a bit free with the drivers
 *    that are available on their GitHub site.
 */

#ifndef BME280_HPP_
#define BME280_HPP_

#include <mutex>             // mutex
#include <stdint.h>          // int16_t, uint16_t

#include "bbb-i2c.hpp"       // I2CBus

#include "bme280_defs.hpp"
#include "bme280_data.hpp"


using bbbi2c::I2CBus;

namespace bosch_bme280
{

class BME280
{

  protected:

	I2CBus* i2cbus;
	uint8_t i2caddr;
	uint8_t chipid;

	CalParams cparams;

	void  GetRegs  ( uint8_t regaddr, uint8_t* data, int len );
	void  SetRegs  ( uint8_t* data, int len );

  public:

	std::mutex mtx;

	BME280 ( I2CBus* bus, uint8_t addr );
   ~BME280 ();

	void      LoadCalParams ();
	 int32_t  Comp32FixedTemp  ( uint32_t unctemp  );
	uint32_t  Comp32FixedPress ( uint32_t uncpress );
	uint32_t  Comp32FixedHumid ( uint32_t unchum   );

	double  CompDoubleTemp  ( uint32_t unctemp  );
	double  CompDoublePress ( uint32_t uncpress );
	double  CompDoubleHumid ( uint32_t unchum   );

	TPH32SensorData    GetSensorData ();
	TPH32CompData      GetComp32FixedData ();
	TPHDoubleCompData  GetCompDoubleData ();

	void  SetConfig ();

	void  Force ();
	void  Reset ( bool reload=false );
	void  Sleep ();

}; // class BME280

} // namespace bosch_bme280

#endif /* BME280_HPP_ */
```
