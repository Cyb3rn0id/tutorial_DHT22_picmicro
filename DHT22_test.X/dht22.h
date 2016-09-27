#include <xc.h>
#include <stdint.h>     // used for uintx_t typedef

// Rule #1 : Write in LAT, read in PORT!
#define DHT22_OUT(level)    	LATAbits.LATA5 = level  // write 1/0 on port
#define DHT22_IN            	PORTAbits.RA5           // reading from the port
#define DHT22_PIN_DIR			TRISAbits.TRISA5        // set port as Input or Output

#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1

// returned states from sensor reading
#define OK			0
#define	TIMEOUT		1
#define CHECKSUM	2

uint8_t  DHT22_data[5]; // data buffer from sensor

#define _XTAL_FREQ 4000000 // 4MHz, used by XC delay routines

extern void DHT22_expect(uint8_t level);
extern uint8_t DHT22_start(void);
extern uint8_t DHT22_read(void);