#include <pic18f4321.h>
#include <xc.h>
#include "MMenu.h"
#include "GLCDGestioLCD.h"
#include "LcTLCD.h"

const char selectUser[] = "1. Select User";
const char newUser[] = "New User";
const char enterName[] = "Enter Name: ";
const char highScore[] = "High score: ";
const char enterNewName[] = "Enter New Name";
const char currentTime[] = "Current Time";
const char timeFormat[] = "(HH:mm): ";
const char Score[] = "Score: ";

unsigned char menuDalt = 0;
char NovaTecla = -1;

void MTMenu(void){
	static char state = 0;
	switch(state) {
		case 0:
			if (LcLliure()) {
				LcClear();
				//LcCursorOff();
				GLCDMostraMenu(menuDalt);
				state = 1;
			}
		break;
		case 1:
			if (NovaTecla == 2) {
				NovaTecla = -1;
				if(menuDalt > 0) menuDalt--;
				state = 0;
			}
			else if (NovaTecla == 8) {
				NovaTecla = -1;
				if(menuDalt < 5) menuDalt++;
				state = 0;
			}
		break;
	}
}

void MsetNovaTecla(char tecla){
    NovaTecla = tecla;
}