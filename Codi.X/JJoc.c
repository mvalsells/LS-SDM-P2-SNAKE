#include "JJoc.h"
#include <xc.h>
#include "AdAdcon.h"
#include "HHora.h"
#include "LcTLCD.h"
#include "AlTAltaveu.h"
#include "SSio.h"
#define NOU_TEMPS 12

signed char usuariActual = -1;
signed char novaDireccio = 0;
const char stringText[] = "T 00:00 | S 000";
signed char JUsuari(void){
    return usuariActual;
}

void JMotor(void){
    static char state = 0;

	switch(state) {
		case 0:
			if (usuariActual != -1 && LcLliure()) {
				SIOStartGame(usuariActual);
				AlPlay();
				LcGotoXY(0,1);
				LcNewString(stringText);
				state++;
			}
		break;
		case 1:
            if (SIOUsuariActual() == -1) {
				AlStop();
				usuariActual = -1;
				state--;
			} else if (HNouSegon() && LcLliure()) {
				HClearNouSegon();
				LcGotoXY(2,1);
				LcNewString(HTempsJocs());
				SIONovaDireccio(NOU_TEMPS);
			}
			else if (novaDireccio > -1) {
				SIONovaDireccio(novaDireccio);
				novaDireccio = -1;
			}
			
		break;
	}
}


void JJuguem(char usuari){
    usuariActual = usuari;
}
void JnovaTecla(char direccio){
    novaDireccio = direccio;
}