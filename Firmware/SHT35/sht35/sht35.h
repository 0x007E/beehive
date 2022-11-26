/*
 * sht35.h
 *
 * Created: 25.11.2022 13:08:37
 *  Author: User
 */ 


#ifndef SHT35_H_
#define SHT35_H_


#define SHT35_CMD_MODE_PERIODIC 0xE000

#include <avr/io.h>

#include "../twi/twi.h"

typedef struct
{
	unsigned char address;
	unsigned char humidity;
	int temperature;
} SHT35_sensor_t;


void sht35_init();
void sht35_sensor(SHT35_sensor_t sensor);
void sht35_sensors(SHT35_sensor_t *sensors, unsigned char length);

#endif /* SHT35_H_ */