/*---------------------------------------------------------------*\
| Datei:          Kommunikation_SHT35_V00
| Projekt:        SMB_LucasP_AlexanderE
| Beschreibung:   Kommunikation zwischen dem SHT35 & der MegaCard 5.5
| Autor:          Lucas Plankensteiner
| Erstellt:       09.11.2022
| Geaendert:
\*---------------------------------------------------------------*/ 

#define SHT35_SENSOR1 0x44
#define SHT35_SENSOR2 0x45

#include <avr/io.h>
#include <util/delay.h>
#include "molibdisplay.h"
#include "sht35/sht35.h"

struct SH35_data_t {
   unsigned char humidity1;
   unsigned char humidity2;
   int temperature1;
   int temperature2;
} sht35_values;

SH35_data2_t sensors[2];

void init (void) 
{
   sensors[0].address = 0x44;
   sensors[1].address = 0x45;
}

int main(void)
{
   display_init();
   init ();
   twi_init(TWI_Master);
   
   while (1)
   {
      int temperature = 0;
      unsigned char humidity = 0;

      sht35_data(SHT35_SENSOR1);
      temperature = sht35_temperature();
      humidity = sht35_humidity();
      
      sht35_values.humidity1 = sht35_humidity();
      sht35_values.temperature1 = sht35_temperature();

      sht35_data(SHT35_SENSOR2);
      temperature = sht35_temperature();
      humidity = sht35_humidity();
      
      sht35_values.humidity2 = sht35_humidity();
      sht35_values.temperature2 = sht35_temperature();

      // Single function
      sh35_sensors(sensors, sizeof(sensors)/sizeof(SH35_data2_t));

      if(temperature > 30)
      {
         PORTC = 0x01;
      }

      if(humidity > 20)
      {
         PORTC = 0x02;
      }
      // Irgendetwas mit den daten machen...

      //display_printf_pos(0,0, "%u", (*SHT35_t.Temp0));
//
      //
      //sht35_data(0x45, data);
      //SHT35_t, data;
      //
      //// Irgendetwas mit den daten machen...
      //display_printf_pos(0,1, "%u", (*SHT35_t.Temp0));



      _delay_ms(5000);     // typischer delay
      display_clear();

   }

   return 0;
}

