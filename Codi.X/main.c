#include <pic18f4321.h>
#include <xc.h>
#include "LcTLCD.h"
#include "TiTTimer.h"

void main(void) {
    //
    //----- INICI INITS -------------
    //
    
    TiInit();
    LcInit(16,2);
    
    //
    //----- FI INITS -------------
    //
    
    LcClear();
    LcPutChar('A');
    return;
}
