#include "JJoc.h"
#include <xc.h>
#include "AdAdcon.h"
#include "HHora.h"
#include "LcTLCD.h"
#include "AlTAltaveu.h"
#include "SSio.h"

signed char usuariActual = -1;
signed char novaDireccio = 0;
__bit borram = 0;
char JUsuari(void){
    return usuariActual;
}


void JMotor(void){
    static char state = 0;

	switch(state) {
		case 0:
			if (usuariActual > -1 && LcLliure()) {
				SIOStartGame(usuariActual);
				//AlPlay();
				LcGotoXY(0,1);
				LcNewString("T 00:00 | S");
				state = 1;
			}
		break;
		case 1:
			if (HNouSegon() && LcLliure()) {
				HClearNouSegon();
				LcGotoXY(2,1);
				LcNewString(HTempsJocs());
				SIONovaDireccio(12);
				state = 1;
			}
			else if (novaDireccio > -1) {
				SIONovaDireccio(novaDireccio);
				novaDireccio = -1;
				state = 1;
			}
			else if (SIOFiJoc()) {
				AlStop();
				usuariActual = -1;
				state = 0;
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