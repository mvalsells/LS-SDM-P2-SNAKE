#include <xc.h>
#include "LcTLCD.h"
#include "UUsuaris.h"

char *userPtr = 0;
signed char usuariActual = -1;
char novaDireccio = -1;
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
				TXREG = userPtr;
				state = 2;
			}
			else if (*userPtr != '\0' && TXSTAbits.TRMT) {
				TXREG = userPtr;
				userPtr++;
			}
		break;
		case 2:
			if (novaDireccio > -1 && TXSTAbits.TRMT) {
				TXREG = novaDireccio;
				novaDireccio = -1;
			}
			else if (PIR1bits.RCIF) {
				LcGotoXY(1,12);
				rebut = RCREG;
				if(rebut != 'X') LcPutChar(rebut);
				state = 3;
			}
		break;
		case 3:
			if (PIR1bits.RCIF && rebut != 'X') {
				LcPutChar(RCREG);
				state = 4;
			}
			else if (rebut == 'X') {
				state = 0;
			}
		break;
		case 4:
			if (PIR1bits.RCIF) {
				LcPutChar(RCREG);
				state = 2;
			}
		break;
	}
}

void SIONovaDireccio(char num){
    novaDireccio = num;
}

void SIOStartGame(char usuari){
    usuariActual = usuari;
}

char SIOFiJoc(void){
    return usuariActual;
}