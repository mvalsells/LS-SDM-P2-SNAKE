#include <pic18f4321.h>
#include <xc.h>
#include "LcTLCD.h"
#include "TiTTimer.h"

#pragma config OSC = HSPLL	    //;Oscillador -> High Speed PLL
#pragma config PBADEN = DIG	    //;PORTB com a Digital (el posem a 0)
#pragma config WDT = OFF	    //;Desactivem el Watch Dog Timer
#pragma config LVP = OFF	    //;Evitar resets eusart

void main(void) {
    //
    //----- INICI INITS -------------
    //
    //-----------PORTS------------
    TRISAbits.TRISA0 = 1;   //axisX
    TRISAbits.TRISA1 = 1;   //axisY

    TRISBbits.TRISB7 = 1;   //pgd
    TRISBbits.TRISB6 = 1;   //pgc
    TRISBbits.TRISB5 = 1;   //pgm
    TRISBbits.TRISB3 = 0; //led tests
    TRISBbits.RB3 = 0;
    //B0 SPK
    
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 1;
    //c5 RS lcd
    //c4 E cld
    //c3 lcd7
    //c2 lcd6
    //c1 lcd5
    //c0 lcd4
    
    //D7 RW display
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD5 = 1;    
    TRISDbits.TRISD4 = 1;
    //D0 telcat F1
    //D1 teclat F2
    //D2 teclat F3
    //D3 teclat F4
    //-----------PORTS-----------
    
    
    
    TiInitTimer();
    LcInit(2,16);
    
    LcClear();
    LcPutString("Missatge");
    LcCursorOn();
    PORTBbits.RB3=1;
    
    
    return;
}