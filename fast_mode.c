#include <pic16f1459.h>
void fast_mode(unsigned char hi_data_byte, unsigned char lo_data_byte)
{
    
    SSP1BUF = hi_data_byte;
    while(!SSP1IF);
    PIR1bits.SSP1IF = 0;
    if(SSPCON2bits.ACKSTAT)
    {
        SSPCON2bits.PEN = 1;
        while(PEN);
        return;
    }
    
    SSP1BUF = lo_data_byte;
    while(!SSP1IF);
    PIR1bits.SSP1IF = 0;
    if(SSPCON2bits.ACKSTAT)
    {
        SSPCON2bits.PEN = 1;
        while(PEN);
        return;
    }
}
