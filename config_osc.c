#include <xc.h>
void config_osc(void)
{
    //FOSC2 = 1;
    /*setup internal clock oscillator**********************/
    OSCCONbits.IRCF3 = 1;           // 4MHz clock setup
    OSCCONbits.IRCF2 = 1;           /* OSCCONbits 5-2 IRCF<3:0>: Internal Oscillator Frequency Select bits
                                    1111 = 16 MHz or 48 MHz HF (see Section 5.2.2.1 ?HFINTOSC?)
                                    1110 = 8 MHz or 24 MHz HF (3x PLL) or 32 MHz HF (4x PLL) (see Section 5.2.2.1 ?HFINTOSC?)
                                    1101 = 4 MHz 
                                    1100 = 2 MHz */
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 0;            // system clock = INTOSC (SCS = 1X), clock freq determined by IRCF<3:0
    OSCCONbits.SCS0 = 0;
}
