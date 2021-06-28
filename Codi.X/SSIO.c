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
				state = 1;
			}
		break;
		case 1:
			if (*userPtr == '\0' && TXSTAbits.TRMT) {
				TXREG = 13;
				state = 2;
			}
			else if (*userPtr != '\0' && TXSTAbits.TRMT) {
				TXREG = *userPtr;
				userPtr++;
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
				state = 3;
			}
		break;
		case 3:
			if (PIR1bits.RCIF && rebut != 'X') {
				LcGotoXY(13,1);
				LcPutChar(RCREG);
				state = 4;
			}
			else if (rebut == 'X' && PIR1bits.RCIF) {
				rebut = RCREG;
				//aqui tenim la ultima score en char;
				if(rebut > UgetScore(usuariActualSIO)){
				    UchangeScore(rebut);
				}
				CToAReset();
				CToAConverteix(rebut);
				state = 5;
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
				state = 6;
			}
		break;
		case 6:
			if (LcLliure()) {
				CToAReset();
				CToAConverteix(UgetScore(usuariActualSIO));
				state = 7;
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
				state = 8;
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

char SIOFiJoc(void){
    return usuariActualSIO;
}