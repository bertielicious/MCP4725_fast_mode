#include <xc.h>
void init_ports(void)
{
    //********TURN OFF ANALOGUE INPUTS**********************
    ANSELA = 0x00;                  // turn off all ADC inputs on PORTA
    ANSELB = 0x00;                  // turn off all ADC inputs on PORTB
    ANSELC = 0x00;                  // turn off all ADC inputs on PORTC
     /* SET DATA DIRECTION FOR GENERAL I/O PINS************************/
    TRISCbits.TRISC0 = 0;   // RED led pin 16
    PORTCbits.RC0 = 0;   
}
