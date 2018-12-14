#include <xc.h>
#include "config.h"
#include "putch.h"
//#include <stdio.h>
//#include <stdarg.h>
void putch(char byte)
{
 while( ! TXIF)
 continue;
 TXREG = byte;
}
