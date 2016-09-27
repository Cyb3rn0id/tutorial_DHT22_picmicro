#include "settings.h"

void system_init(void)
    {
    // oscillator setup
    OSCCONbits.SPLLEN=0;    // PLL disabled
    OSCCONbits.IRCF=0b1101; // internal oscillator @4MHz
    OSCCONbits.SCS=0b10;    // use internal oscillator
    
    // IO setup
    ANSELA=0;               // all ports as digital
    ADCON0bits.ADON=0;      // ADC disabled
    DACCON0bits.DACEN=0;    // DAC disabled
    CM1CON0bits.C1ON=0;     // Comparator disabled
        
	// TIMER 1 setup
    // Timer 1 is adjusted for incrementing 1 unit every 1uS
	T1CONbits.TMR1CS=0b00;  // Source : Fosc/4 (=> 1MHz)
    T1CONbits.T1CKPS=0b00;  // Prescaler 1:1
    T1CONbits.nT1SYNC=1;    // don't synchronize
    T1GCONbits.TMR1GE=0;    // Timer 1 as counter, not gated
    TMR1ON=1; // Timer start
    
    // USART
    // USART is adjusted for working @ 9600baud
    TXSTAbits.TX9=0;        // 8 bit TX
    TXSTAbits.TXEN=1;       // TX enabled
    TXSTAbits.SYNC=0;       // asinchronous
    TXSTAbits.BRGH=1;       // high speed baud rate generator
    RCSTAbits.SPEN=1;       // serial port enabled
    RCSTAbits.RX9=0;        // 8 bit RX
    RCSTAbits.CREN=1;       // RX enabled
    RCSTAbits.ADDEN=0;      // no address detection
    BAUDCONbits.ABDEN=0;    // no autobaud detection
    BAUDCONbits.BRG16=1;    // 16bit baud rate generator
    // setup baud rate generator
    // see datasheet pag.191 for baudate 9600 using 16bit baudrate generator
    // and high speed
    SPBRGL=103;
   	SPBRGH=0;
    
    // wait until osccilator stable
	while (!OSCSTATbits.HFIOFR);
    }    
