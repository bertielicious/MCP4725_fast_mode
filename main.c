/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 27 November 2018, 14:08
 */
#include <math.h>
#include "config.h"
#include <xc.h>
#include "stdio.h"
#include "main.h"
#include "init_ports.h"
#include "config_osc.h"
#include "set_usart.h"
#include "putch.h"
#include "dac_write.h"
#include "fast_mode.h"

void main(void) 
{
    int x, y = 0;
    init_ports();
    config_osc();
    set_usart();
    printf("MCP4725 12-bit DAC controlled over i2c\n");
    
    TRISBbits.TRISB4 = 1;   // SDA is an input 
    TRISBbits.TRISB6 = 1;   // SCL is an input
    SDA = 1;                // bus idle condition
    SCL = 1;
    
    RED_LED = 1;            // RED LED lit shows that code is running
    
    /*Enable i2c master mode, SCL = FOSC/(4 * (SPPADD + 1))*/
    SSPCON1bits.SSPEN = 1;       // enables i2c SDA and SCL pins
    SSPCON1bits.SSP1M3 = 1;
    SSPCON1bits.SSP1M2 = 0;
    SSPCON1bits.SSP1M1 = 0;
    SSPCON1bits.SSP1M0 = 0;
    SSPADD = 0x04;              // SCL = 400kHz, Fosc = 16MHz
                                // SSPADD = (Fosc/(4 * SCL)) - 1
    
    PIR1bits.SSP1IF = 0;    // clear the SSP interrupt flag 
    SSPSTATbits.SMP = 0;    // slew rate disabled for standard speed mode
    
    //unsigned char higher = 0xff;    //255  normal mode 100 kbps
    //unsigned char lower = 0x0f;     //15
    
    unsigned char higher = 0x0f;    //15  fast mode 400kbps
    unsigned char lower = 0xff;     //255
    
    SSPCON2bits.SEN = 1;    // initiate start condition on SDA and SCL pins.
    while(SEN);             // SEN is automatically cleared in hardware SEN = 0 indicates Idle condition of SCL & SDA high
    PIR1bits.SSP1IF = 0;    // clear Synchronous Serial Port interrupt flag
    
    SSP1BUF = 0xC0;             //load address byte into SSP1BUF register MSB first
    while(!SSP1IF);          // wait for MSSP interrupt = address_byte has been transmitted
    PIR1bits.SSP1IF = 0;     // clear Synchronous Serial Port interrupt flag
    if(SSPCON2bits.ACKSTAT)     // if Ack was not received by the Master
    {
        SSPCON2bits.PEN = 1;    // initiate the Stop condition
        while(PEN);             // wait for Stop condition Idle
       
    }
    while(1)
    {
        RED_LED = ~RED_LED;                 // diagnostic LED to show code is running
       
         for(x = 0; x <=higher; x++)
        {
            for(y = 0; y <= lower; y++)
            {    
                fast_mode(x&0x0f,y);
            }
        }
        for(x = higher; x >=0; x--)
        {
            for(y = lower; y > 0; y--)
            {                
                fast_mode(x&0x0f,y);
            }
        }
            
    }
}

   
    
