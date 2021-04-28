#include <pic18f4321.h>
#include <xc.h>
#include "LcTLCD.h"
#include "TiTTimer.h"

#pragma config OSC = INTIO2	    //;Oscillador -> High Speed PLL
#pragma config PBADEN = DIG	    //;PORTB com a Digital (el posem a 0)
#pragma config WDT = OFF	    //;Desactivem el Watch Dog Timer
#pragma config LVP = OFF	    //;Evitar resets eusart

void main(void) {
    //
    //----- INICI INITS -------------
    //
    
    //Init osc
   // OSCCONbits.IRCF = 0x06;
    //OSCCONbits.SCS1 = 1;
    
    TiInitTimer();
    LcInit(16,2);
    
    
    //
    //----- FI INITS -------------
    //
    
    //LcClear();
    //LcPutChar('A');
    //LcCursorOn();
    
    TRISBbits.TRISB3=0;
    PORTBbits.RB3=1;
    return;
}
