/*
 * sensors.c
 *
 *  Created on: 16 Nis 2023
 *      Author: anil
 */


#include "sensors.h"

/* These values are also used in main function with extern keyword */
float temperature;
float humidity;
float co2;
static float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type);

void	measure_temperature(uint8_t device_address)
{
	// Assume a float temperature value is obtained from raw values
	temperature = i2c_sensor_read(device_address, TEMPERATURE_SENSOR);
}

void	measure_humidity(uint8_t device_address)
{
	// Assume a float humidity value is obtained from raw values
	humidity = i2c_sensor_read(device_address, HUMIDITY_SENSOR);
}

void	measure_co2(uint8_t device_address)
{
	// Assume a float co2 value is obtained from raw values
	co2 = i2c_sensor_read(device_address, CO2_SENSOR);
}
