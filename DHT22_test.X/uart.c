#include "uart.h"

void putch(uint8_t data)
    {
    while (!TXIF)
        {continue;}
    TXREG=data;
    }