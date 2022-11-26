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
#include "oled/molibdisplay.h"
#include "sht35/sht35.h"

SHT35_sensor_t sensors[] = {
    {
        0x44, 0, 0
    },
    {
        0x45, 0, 0
    }
};

void init (void)
{
    DDRC = 0xFF;
}

int main(void)
{
    init ();
    display_init();
    sht35_init();
    
    while (1)
    {
        sht35_sensors(sensors, sizeof(sensors)/sizeof(SHT35_sensor_t));

        PORTC = 0x00;

        for(unsigned char i=0; i < sizeof(sensors)/sizeof(SHT35_sensor_t); i++)
        {
            PORTC++;
        
            display_printf_pos(0,i, "%i", sensors[i].temperature);
            display_printf_pos(0,i, "%u", sensors[i].humidity);
        }

        _delay_ms(5000);
        display_clear();
    }
}

