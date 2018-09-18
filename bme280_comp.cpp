/*
 * bme280_comp.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: JSRagman
 *
 *  Description:
 *     Compensation functions for the Bosch Sensortec BME280
 *     combined humidity and pressure sensor.
 *
 *     Derived from bme280.c, which is available at
 *     https://github.com/BoschSensortec/BME280_driver
 *
 *  Notes:
 *    1. 32-bit fixed-point compensation
 *      a. Temperature - divide the output by 100 to get temperature
 *         in degrees centigrade.
 *      b. Pressure - output is in pascals (Pa).
 *      c. Humidity - divide the output by 1024 to get percent
 *         relative humidity.
 *    2. Floating-point compensation
 *      a. Temperature - output is in degrees centigrade.
 *      b. Pressure - output is in pascals (Pa).
 *      c. Humidity - output is in percent relative humidity.
 */


#include "bme280.hpp"


namespace bosch_bme280
{


/*
 * int32_t BME280::Comp32FixedTemp(uint32_t unctemp)
 *
 * Description:
 *   Applies 32-bit fixed-point compensation to a temperature reading.
 *   Also generates a temperature value (tfine) which is used to
 *   compensate associated pressure and humidity readings.
 *
 * Parameters:
 *   unctemp - an uncompensated temperature value
 *
 * Returns:
 *   Returns a 32-bit integer that has units of 1/100 degrees centigrade.
 *
 *   cparams.tfine - When this function exits, tfine will contain a value
 *   that can be used to compensate associated pressure and humidity
 *   readings.
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
int32_t BME280::Comp32FixedTemp(uint32_t unctemp)
{
	if (!cparams.loaded) this->LoadCalParams();

	int32_t temperature;
	int32_t temp_min = -4000;
	int32_t temp_max =  8500;

	int32_t t1 = (int32_t)cparams.t1;
	int32_t t2 = (int32_t)cparams.t2;
	int32_t t3 = (int32_t)cparams.t3;

	int32_t v1;
	int32_t v2;

	v1 = (int32_t)((unctemp/8)-(t1*2));
	v1 = (v1*t2)/2048;

	v2 = (int32_t)((unctemp/16)-t1);
	v2 = (((v2*v2)/4096)*t3)/16384;
	cparams.tfine = v1 + v2;

	temperature = (cparams.tfine * 5 + 128) / 256;

	if (temperature < temp_min)
		temperature = temp_min;
	else if (temperature > temp_max)
		temperature = temp_max;

	return temperature;
}

/*
 * uint32_t BME280::Comp32FixedPress(uint32_t uncpress)
 *
 * Description:
 *   Applies 32-bit fixed-point compensation to a pressure reading.
 *
 * Parameters:
 *   uncpress - an uncompensated pressure value
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
uint32_t BME280::Comp32FixedPress(uint32_t uncpress)
{
	 int32_t v1, v2, v3, v4;
	uint32_t v5;
	uint32_t pressure;
	uint32_t p_min = 30000;
	uint32_t p_max = 110000;

	v1 = (cparams.tfine / 2) - 64000;
	v2 = (((v1/4) * (v1/4)) / 2048) * ((int32_t)cparams.p6);
	v2 = v2 + ((v1 * ((int32_t)cparams.p5)) * 2);
	v2 = (v2 / 4) + (((int32_t)cparams.p4) * 65536);
	v3 = (cparams.p3 * (((v1 / 4) * (v1 / 4)) / 8192)) / 8;
	v4 = (((int32_t)cparams.p2) * v1) / 2;
	v1 = (v3 + v4) / 262144;
	v1 = (((32768 + v1)) * ((int32_t)cparams.p1)) / 32768;

	if (v1) {
		v5 = (uint32_t)((uint32_t)1048576) - uncpress;
		pressure = ((uint32_t)(v5 - (uint32_t)(v2 / 4096))) * 3125;
		if (pressure < 0x80000000)
			pressure = (pressure << 1) / ((uint32_t)v1);
		else
			pressure = (pressure / (uint32_t)v1) * 2;

		v1 = (((int32_t)cparams.p9) * ((int32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
		v2 = (((int32_t)(pressure / 4)) * ((int32_t)cparams.p8)) / 8192;
		pressure = (uint32_t)((int32_t)pressure + ((v1 + v2 + cparams.p7) / 16));

		if (pressure < p_min)
			pressure = p_min;
		else if (pressure > p_max)
			pressure = p_max;
	} else {
		pressure = p_min;
	}

	return pressure;
}

/*
 * uint32_t BME280::Comp32FixedHumid(uint32_t unchum)
 *
 * Description:
 *   Applies 32-bit fixed-point compensation to a humidity reading.
 *
 * Parameters:
 *   unchum - an uncompensated humidity value
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
uint32_t BME280::Comp32FixedHumid(uint32_t unchum)
{
	if (!cparams.loaded) this->LoadCalParams();

	int32_t v1, v2, v3, v4, v5;
	uint32_t humidity;
	uint32_t hu_max = 102400;

	v1 = cparams.tfine - ((int32_t)76800);
	v2 = (int32_t)(unchum * 16384);
	v3 = (int32_t)(((int32_t)cparams.h4) * 1048576);
	v4 = ((int32_t)cparams.h5) * v1;
	v5 = (((v2 - v3) - v4) + (int32_t)16384) / 32768;
	v2 = (v1 * ((int32_t)cparams.h6)) / 1024;
	v3 = (v1 * ((int32_t)cparams.h3)) / 2048;
	v4 = ((v2 * (v3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
	v2 = ((v4 * ((int32_t)cparams.h2)) + 8192) / 16384;
	v3 = v5 * v2;
	v4 = ((v3 / 32768) * (v3 / 32768)) / 128;
	v5 = v3 - ((v4 * ((int32_t)cparams.h1)) / 16);
	v5 = (v5 < 0 ? 0 : v5);
	v5 = (v5 > 419430400 ? 419430400 : v5);
	humidity = (uint32_t)(v5 / 4096);

	if (humidity > hu_max)
		humidity = hu_max;

	return humidity;
}

/*
 * double BME280::CompDoubleTemp(uint32_t unctemp)
 *
 * Description:
 *   Applies double floating-point compensation to a temperature
 *   reading.
 *
 * Parameters:
 *   unctemp - an uncompensated temperature value
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
double BME280::CompDoubleTemp(uint32_t unctemp)
{
	if (!cparams.loaded) this->LoadCalParams();

	double v1;
	double v2;
	double temperature;
	double utemp = (double)unctemp;
	double t_min = -40;
	double t_max =  85;

	double t1 = (double)cparams.t1;
	double t2 = (double)cparams.t2;
	double t3 = (double)cparams.t3;

	v1 = (utemp/16384.0  - t1/1024.0) * t2;
	v2 = (utemp/131072.0 - t1/8192.0);
	v2 = (v2*v2) * t3;

	cparams.tfine = (int32_t)(v1 + v2);
	temperature = (v1+v2)/5120.0;

	if (temperature < t_min)
		temperature = t_min;
	else if (temperature > t_max)
		temperature = t_max;

	return temperature;
}

/*
 * double BME280::CompDoublePress(uint32_t uncpress)
 *
 * Description:
 *   Applies double floating-point compensation to a pressure
 *   reading.
 *
 * Parameters:
 *   uncpress - an uncompensated pressure value
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
double BME280::CompDoublePress(uint32_t uncpress)
{
	double v1;
	double v2;
	double v3;
	double pressure;
	double p_min =  30000.0;
	double p_max = 110000.0;

	v1 = ((double)cparams.tfine/2.0) - 64000.0;
	v2 = v1*v1 * ((double)cparams.p6)/32768.0;
	v2 = v2+v1 * ((double)cparams.p5) * 2.0;
	v2 = (v2/4.0) + (((double)cparams.p4) * 65536.0);
	v3 = ((double)cparams.p3)*v1*v1/524288.0;
	v1 = (v3 + ((double)cparams.p2) * v1) / 524288.0;
	v1 = (1.0 + v1 / 32768.0) * ((double)cparams.p1);

	if (v1) {
		pressure = 1048576.0 - (double)uncpress;
		pressure = (pressure - (v2/4096.0)) * 6250.0 / v1;
		v1 = ((double)cparams.p9) * pressure * pressure / 2147483648.0;
		v2 = pressure * ((double)cparams.p8) / 32768.0;
		pressure = pressure + (v1 + v2 + ((double)cparams.p7)) / 16.0;

		if (pressure < p_min)
			pressure = p_min;
		else if (pressure > p_max)
			pressure = p_max;
	} else {
		pressure = p_min;
	}

	return pressure;
}

/*
 * double BME280::CompDoubleHumid(uint32_t unchum)
 *
 * Description:
 *   Applies double floating-point compensation to a humidity
 *   reading.
 *
 * Parameters:
 *   unchum - an uncompensated humidity value
 *
 * Namespace:
 *   bosch_bme280
 *
 * Header File(s);
 *   bme280.hpp
 */
double BME280::CompDoubleHumid(uint32_t unchum)
{
	double humidity;
	double hu_min = 0.0;
	double hu_max = 100.0;
	double v1, v2, v3, v4, v5, v6;

	v1 = ((double)cparams.tfine) - 76800.0;
	v2 = (((double)cparams.h4) * 64.0 + (((double)cparams.h5) / 16384.0) * v1);
	v3 = unchum - v2;
	v4 = ((double)cparams.h2) / 65536.0;
	v5 = (1.0 + (((double)cparams.h3) / 67108864.0) * v1);
	v6 = 1.0 + (((double)cparams.h6) / 67108864.0) * v1 * v5;
	v6 = v3*v4*v5*v6;
	humidity = v6 * (1.0 - ((double)cparams.h1) * v6 / 524288.0);

	if (humidity > hu_max)
		humidity = hu_max;
	else if (humidity < hu_min)
		humidity = hu_min;

	return humidity;
}


} // namespace bosch_bme280

