#include "JJoc.h"
#include <xc.h>
#include "AdAdcon.h"
#include "HHora.h"
#include "LcTLCD.h"
#include "AlTAltaveu.h"

signed char usuariActual = -1;
char novaDireccio = 0;

char JUsuari(void){
    return usuariActual;
}


void JMotor(void){
    static char state = 0;
    switch(state) {
		case 0:
			if (usuariActual > -1 && LcLliure()) {
				//Enviar nom + startgame EUSART;
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
				state = 1;
			}
			else if (novaDireccio != -1) {
				//EuNovaDireccio(novaDireccio);
				state = 1;
			}/*
			else if (EuNovaPuntuacio() && LcLliure() && EuFiJoc()==0) {
				LcGotoXY(11,1);
				LcNewString(EuGetPuntiacio);
				state = 1;
			}
			else if (EuFiJoc()) {
				AlStop();
				state = 0;
			}*/
		break;
	}
}


void JJuguem(char usuari){
    usuariActual = usuari;
}
void JnovaTecla(char direccio){
    novaDireccio = direccio;
}