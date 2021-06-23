#include <xc.h>
#include "LcTLCD.h"
#include "UUsuaris.h"

char *userPtr = 0;
signed char usuariActual = -1;
signed char direccio = -1;
char rebut;

void SIOMotor(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (usuariActual > -1) {
				userPtr = UgetUserName(usuariActual);
				state = 1;
			}
		break;
		case 1:
			if (*userPtr == '\0' && TXSTAbits.TRMT) {
				usuariActual = -1;
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
				LcClear();
				LcGotoXY(7,0);
				rebut = RCREG;
				if(rebut > UgetScore(usuariActual)){
				    UchangeScore(rebut);
				} 
				usuariActual = -1;
				state = 0;
			}
		break;
		case 4:
			if (PIR1bits.RCIF) {
				LcGotoXY(14,1);
				LcPutChar(RCREG);
				state = 2;
			}
		break;
	}
}

void SIONovaDireccio(char num){
    direccio = num;
}

void SIOStartGame(char usuari){
    usuariActual = usuari;
}

char SIOFiJoc(void){
    return usuariActual;
}