
#include "sht35.h"

void sht35_init()
{
    twi_init(TWI_Master);
}

void sht35_sensor(SHT35_sensor_t sensor)
{
    twi_start();
    // Chip Adresse
    twi_address(sensor.address, TWI_Write);
    
    // Command
    twi_set((unsigned char)(SHT35_CMD_MODE_PERIODIC>>8));
    twi_set((unsigned char)(SHT35_CMD_MODE_PERIODIC));

    // RepeatedStart
    twi_start();
    twi_address(sensor.address, TWI_Read);

    unsigned char temp;

    // Data
    // ---------------------
    // [0] = Temperature MSB
    // [1] = Temperature LSB
    // [2] = Temperature CRC
    // [3] = Humidity MSB
    // [4] = Humidity LSB
    // [5] = Humidity CRC
    // ---------------------
    
    for(unsigned char i=0; i < 6; i++)
    {

        if (i == 5)
        {
            twi_get(&temp, TWI_NACK);
            break;
        }


        twi_get(&temp, TWI_ACK);

        switch (i)
        {
            case 0:
            sensor.temperature &= 0xFF00 & (temp<<8);
            break;
            case 1:
            sensor.temperature |=  0x00FF & temp;
            break;
            case 3:
            sensor.humidity &= 0xFF00 & (temp<<8);
            break;
            case 4:
            sensor.humidity |=  0x00FF & temp;
            break;
        }
    }
    
    // Beenden der Übertragung
    twi_stop();
}

void sht35_sensors(SHT35_sensor_t *sensors, unsigned char length)
{
    for (unsigned char i=0; i < length; i++)
    {
        sht35_sensor(sensors[i]);
    }
}