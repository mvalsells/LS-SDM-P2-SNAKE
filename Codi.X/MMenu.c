#include <pic18f4321.h>
#include <xc.h>
#include "MMenu.h"
#include "GLCDGestioLCD.h"
#include "LcTLCD.h"
#include "HHora.h"

char selectUser[] = "1. Select User";
char newUser[] = "New User";
const char enterName[] = "Enter Name: ";
const char highScore[] = "High score: ";
const char enterNewName[] = "Enter New Name";
const char currentTime[] = "Current Time";
const char timeFormat[] = "(HH:mm): ";
const char Score[] = "Score: ";
 

unsigned char menuDalt = 0;
signed char NovaTecla = -1;
char horaTmp[5];


void MTMenu(void){
	static char state = 0;
    switch(state) {
		case 0:
			if (LcLliure()) {
				LcClear();
				SiFerMenu();
				GLCDMostraMenu(menuDalt);
				NovaTecla = -1;
				state = 1;
			}
		break;
		case 1:
			if (NovaTecla == 2) {
				if(menuDalt > 0) menuDalt--;
				state = 0;
			}
			else if (NovaTecla == 8) {
				if(menuDalt < 5) menuDalt++;
				state = 0;
			}
			else if (NovaTecla == 10 && menuDalt == 4) {
				LcClear();
				NoFerMenu();
				state = 2;
			}
			else if (NovaTecla == 10 && menuDalt == 5) {
				LcClear();
				NoFerMenu();
				LcNewString("Enter new time");
				state = 11;
			}
		break;
		case 2:
			if (LcLliure()) {
				LcNewString("Current Time");
				state = 4;
			}
		break;
		case 3:
			if (HNouMinut() && NovaTecla != 11 && LcLliure()) {
				HClearNouMinut();
				LcClear();
				state = 2;
			}
			else if (NovaTecla == 11 && LcLliure()) {
				state = 0;
			}
		break;
		case 11:
			if (LcLliure()) {
				LcGotoXY(0,1);
				LcNewString("(HH:MM): ");
				state = 5;
			}
		break;
		case 5:
			if (NovaTecla >= 0 && NovaTecla <= 2) {
				horaTmp[0] = NovaTecla+48;
				LcPutChar(horaTmp[0]);
				NovaTecla = -1;
				state = 6;
			}
		break;
		case 6:
			if (NovaTecla >= 0 && NovaTecla <=9) {
				horaTmp[1] = NovaTecla+48;
				LcPutChar(horaTmp[1]);
				NovaTecla = -1;
				state = 7;
			}
		break;
		case 7:
			LcPutChar(':');
			state = 8;
		break;
		case 8:
			if (NovaTecla >= 0 && NovaTecla <= 5) {
				horaTmp[2] = NovaTecla+48;
				LcPutChar(horaTmp[2]);
				NovaTecla = -1;
				state = 9;
			}
		break;
		case 9:
			if (NovaTecla >= 0 && NovaTecla <=9) {
				horaTmp[3] = NovaTecla+48;
				LcPutChar(horaTmp[3]);
				NovaTecla = -1;
				state = 10;
			}
		break;
		case 10:
			if (NovaTecla == 10) {
				HActualitzarHora(horaTmp);
				NovaTecla = -1;
				state = 0;
			}
		break;
		case 4:
			if (LcLliure()) {
				LcGotoXY(0,1);
				LcNewString(HGetTime());
				state = 3;
			}
		break;
	}
}

void MsetNovaTecla(char tecla){
    NovaTecla = tecla;
}