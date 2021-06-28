#include <pic18f4321.h>
#include <xc.h>
#include "LcTLCD.h"
#include "TiTTimer.h"
#include "AlTAltaveu.h"
#include "MMenu.h"
#include "TeTeclat.h"
#include "GLCDGestioLCD.h"
#include "HHora.h"
#include "Ssms.h"
#include "AdAdcon.h"
#include "UUsuaris.h"
#include "JJoc.h"
#include "SSio.h"
#include "CtoA.h"

#pragma config OSC = HSPLL	    //;Oscillador -> High Speed PLL
#pragma config PBADEN = DIG	    //;PORTB com a Digital (el posem a 0)
#pragma config WDT = OFF	    //;Desactivem el Watch Dog Timer
#pragma config LVP = OFF	    //;Evitar resets eusart

void __interrupt() high_rsi(){
    _TiRSITimer();
}

void init_ports(void){
    //TRISAbits.TRISA0 = 1;   //axisX
    //TRISAbits.TRISA1 = 1;   //axisY
    TRISA = 0x03;//00000011

    //TRISBbits.TRISB7 = 1;   //pgd
    //TRISBbits.TRISB6 = 1;   //pgc
    //TRISBbits.TRISB5 = 1;   //pgm
    //B0 SPK
    TRISB = 0xE0;//11100000
    LATBbits.LATB3 = 0;
    LATBbits.LATB0 = 0;
    
    //TRISCbits.TRISC7 = 1;
    //TRISCbits.TRISC6 = 1;
    //c5 RS lcd
    //c4 E cld
    //c3 lcd7
    //c2 lcd6
    //c1 lcd5
    //c0 lcd4
    TRISC = 0xC0;//110000000
    
    //D7 RW display
    //TRISDbits.TRISD6 = 1;
    //TRISDbits.TRISD5 = 1;    
    //TRISDbits.TRISD4 = 1;
    //D0 telcat F1
    //D1 teclat F2
    //D2 teclat F3
    //D3 teclat F4
    TRISD = 0x8F; //10001111
    LATD = 0x00;
}
void init_eusart(void){
    TXSTA = 0x24; //00100100
    RCSTA = 0x90;//10010000
    BAUDCON = 0x08;
    SPBRGH = 0x04;  //high(1040) -> high(0000 0100 0001 0000) -> 0000 0100 -> 0x04
    SPBRG = 0x10;   //low(1040) -> low(0000 0100 0001 0000) -> 0001 0000 -> 0x10
}


void main(void) {
    init_ports();
    init_eusart(); 
    
    TiInitTimer();
    AlInit();
    AdInit();
    LcInit(2,16);
    TeInit();
    GLCDInit();
    HInit();
    Sinit();
    //UsersInit();//no fa res
    while(1){
        //AlTAltaveu();
        GLCDMotor();
        UUsuarisNouUsuari();
        MTMenu();
        JMotor();
        SIOMotor();
        CtoA();
             
        //HHoraMotor();
        //AdMotor();
        
        TeTeclat();//antapenultim
        SMotor(); //penultim
        LcLCD();//ultim
    }
    return;
}