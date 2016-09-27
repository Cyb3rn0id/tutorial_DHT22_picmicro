/*
 * Tutorial for a DHT22 Humidity/Temperature sensor
 *
 * Author:          Bernardo Giovanni
 * Sito:            http://www.settorezero.com
 * MCU:             Microchip PICmicro PIC12F1822
 * Compiler:        Microchip XC8 ver 1.38
 * Ide:             MPLAB X Ide ver 3.35 
 *
 * PLESE DO NOT REDISTRIBUTE CODE OR PART OF IT WITHOUT AUTHOR PERMISSION
 * 
 * PER PIACERE NON RIDISTRIBUITE IL CODICE O PARTE DI ESSO SENZA
 * CHIEDERE L'AUTORIZZAZIONE ALL'AUTORE
 * 
 */

#include "config.h"
#include <xc.h>
#include <stdint.h>     // used for uintx_t typedef
#include <stdio.h>      // used for printf
#include <stdbool.h>    // used for true,false definitions
#include "settings.h"   // system setup
#include "dht22.h"      // my DHT22 libraries
#include "uart.h"       // for putch

void main(void)
	{
    system_init();
    
    while(true)
		{
		// adjusted %UR/Temp data
		int16_t te=0;
        int16_t hr=0;
		static bit t_negative=false;
        
		uint8_t dht22_status=0;
        dht22_status=DHT22_read();

        switch(dht22_status)
            {
            case CHECKSUM:
                printf("Error: Bad Checksum\n\r");
                break;
                            
            case TIMEOUT:
                printf("Error: Response Timeout\n\r");
                break;
						
			case OK:
                hr=(DHT22_data[0]<<8) | DHT22_data[1]; // entire Humidity value
                te=(DHT22_data[2]<<8) | DHT22_data[3]; // entire Temperature value
				
				// check if temperature is below 0 celsius
				if (te & 0x8000) // bit 16 is 1 ?
					{
					t_negative=true;
					te &= 0x7FFF; // reset bit 16
					}

                printf("R. Humidity: %u.%u %%\n\r", hr/10, (hr-((hr/10)*10)));
                printf("Temperature: ");
				if (t_negative)
					{
					printf("-");
					}
				printf("%u.%u C\n\r", te/10, (te-((te/10)*10)));
                break;
            }

        printf("-------------------\n\r");

		// It must be pass at least 2 seconds between readings
        // I allow 3 seconds (15*200mS)
        for (uint8_t s=0; s<15; s++)
            {
            __delay_ms(200);    
            }
		} // \while
	} // \main