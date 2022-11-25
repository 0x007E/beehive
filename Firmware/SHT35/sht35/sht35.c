
#include "sht35.h"

struct SH35_data2_t {
   unsigned char address;
   unsigned char humidity;
   int temperature;
};

static unsigned char data[6];

// Daten
// [0] =
// [1] =
// [2] = 
// ... 

int sht35_temperature()
{
   return (data[0]<<8) | data[1];
}

unsigned char sht35_humidity()
{
   return (data[0]<<8) | data[1];
}

void sht35_data(unsigned char address)
{
   twi_start(); // Startet die Kommunikation der I²c Library
   // Chip Adresse
   twi_address(address, TWI_Write);
   // Command
   twi_set(0xE0);
   twi_set(0x00);
   // RepeatedStart
   twi_start();
   twi_address(address, TWI_Read);

   // Optimieren mit for schleife
   for(signed char i = 5; i >= 0; i--)
   {
      if (i == 0)
      {
         twi_get(&data[i], TWI_NACK);
      }
      else
      {
         twi_get(&data[i], TWI_ACK);
      }
   }
   
   // Beenden der Übertragung
   twi_stop();
}

sh35_sensors(SH35_data2_t *sensors, unsigned char length)
{
   for (unsigned char i=0; i < length; i++)
   {
      twi_start(); // Startet die Kommunikation der I²c Library
      // Chip Adresse
      twi_address(sensors[i].address, TWI_Write);
      // Command
      twi_set(0xE0);
      twi_set(0x00);
      // RepeatedStart
      twi_start();
      twi_address(address, TWI_Read);

      unsigned char temp;

      // Optimieren mit for schleife
      for(signed char j = 5; j >= 0; j--)
      {
         if (j == 0)
         {
            twi_get(&data[j], TWI_NACK);
         }
         else
         {
            twi_get(&temp, TWI_ACK);

            if(j == 3)
            {
               sensors[i].temperature &= 0x00FF & temp;
            }
            else if(j == 2)
            {
               sensors[i].temperature |= (temp<<8);
            }
         }
      }
   
      // Beenden der Übertragung
      twi_stop();
   }
}