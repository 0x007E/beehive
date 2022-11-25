/*
 * sht35.h
 *
 * Created: 25.11.2022 13:08:37
 *  Author: User
 */ 


#ifndef SHT35_H_
#define SHT35_H_

#include <avr/io.h>

#include "../twi/twi.h"

void sh35_sensors(SH35_data2_t *sensors, unsigned char length);

int sht35_temperature();
unsigned char sht35_humidity();
void sht35_data(unsigned char address);

#endif /* SHT35_H_ */