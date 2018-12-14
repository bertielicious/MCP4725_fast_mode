
#include <pic16f1459.h>

void dac_write (unsigned char control_byte, unsigned char hi_data_byte, unsigned char lo_data_byte)
{
    /*SSPCON2bits.SEN = 1;    // initiate start condition on SDA and SCL pins.
    while(SEN);             // SEN is automatically cleared in hardware SEN = 0 indicates Idle condition of SCL & SDA high
    PIR1bits.SSP1IF = 0;    // clear Synchronous Serial Port interrupt flag
    
    SSP1BUF = addr_byte;     //load address byte into SSP1BUF register MSB first
    while(!SSP1IF);          // wait for MSSP interrupt = address_byte has been transmitted
    PIR1bits.SSP1IF = 0;     // clear Synchronous Serial Port interrupt flag
    if(SSPCON2bits.ACKSTAT)     // if Ack was not received by the Master
    {
        SSPCON2bits.PEN = 1;    // initiate the Stop condition
        while(PEN);             // wait for Stop condition Idle
        return;
    }*/
    
    SSP1BUF = control_byte;     //load control byte into SSP1BUF register MSB first
    while(!SSP1IF);             // wait for MSSP interrupt = control_byte has been transmitted
    PIR1bits.SSP1IF = 0;        // clear Synchronous Serial Port interrupt flag
    if(SSPCON2bits.ACKSTAT)     // if Ack was not received by the Master
    {
        SSPCON2bits.PEN = 1;    // initiate the Stop condition
        while(PEN);             // wait for Stop condition Idle
        return;
    }
    
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
