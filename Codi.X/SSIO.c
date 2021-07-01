#include <xc.h>
#include "LcTLCD.h"
#include "UUsuaris.h"
#include "CtoA.h"

char *userPtr = 0;
signed char usuariActualSIO = -1;
signed char direccio = -1;
unsigned char rebut;


void SIOMotor(void) {
	static char state = 0;
    switch(state) {
		case 0:
			if (usuariActualSIO > -1) {
				userPtr = UgetUserName(usuariActualSIO);
				state++;
			}
		break;
		case 1:
            if(TXSTAbits.TRMT){
                if (*userPtr == '\0') {
				TXREG = 13;
				state++;
                }else{
                    TXREG = *userPtr;
				userPtr++;
                }
            }
		break;
		case 2:
			if (direccio != -1 && TXSTAbits.TRMT) {
				TXREG = direccio;
				direccio = -1;
			}
			else if (PIR1bits.RCIF) {
				LcGotoXY(12,1);
				rebut = RCREG;
				LcPutChar(RCREG);
				state++;
			}
		break;
		case 3:
            if(PIR1bits.RCIF){
                if(rebut != 'X'){
                    LcGotoXY(13,1);
                    LcPutChar(RCREG);
                    state++;
                }else{
                    rebut = RCREG;
                    //aqui tenim la ultima score en char;
                    if(rebut > UgetScore(usuariActualSIO)){
                        UchangeScore(usuariActualSIO, rebut);
                    }
                    //CToAReset();
                    CToAConverteix(rebut);
                    state = 5;
                }
            }
		break;
		case 4:
			if (PIR1bits.RCIF) {
				LcGotoXY(14,1);
				LcPutChar(RCREG);
				state = 2;
			}
		break;
		case 5:
			if (LcLliure() && CToAHaAcabat() == 250) {
				LcClear();
				LcGotoXY(7,0);
				LcNewString(CToAobtenir());
				state++;
			}
		break;
		case 6:
			if (LcLliure()) {
				//CToAReset();
				CToAConverteix(UgetScore(usuariActualSIO));
				state++;
			}
		break;
		case 8:
			if (LcLliure()) {
				state = 0;
			}
		break;
		case 7:
			if (LcLliure() && CToAHaAcabat() == 250) {
				LcGotoXY(12,1);
				LcNewString(CToAobtenir());
				usuariActualSIO = -1;
				state++;
			}
		break;
	}

}

void SIONovaDireccio(char num){
    direccio = num;
}

void SIOStartGame(char usuari){
    usuariActualSIO = usuari;
}

signed char SIOUsuariActual(void){
    return usuariActualSIO;
}