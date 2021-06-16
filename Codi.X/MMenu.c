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



void MTMenu(void){
	static char state = 0;

	switch(state) {
		case 0:
			if (LcLliure()) {
                SiFerMenu();
				LcClear();
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
                NoFerMenu();
				LcClear();
                NovaTecla = -1;
				LcNewString("Current Time");
				state = 2;
			}
		break;
		case 2:
			if (LcLliure()) {
				LcGotoXY(0,1);
				LcNewString(HGetTime());
				state = 3;
			}
            else if(LcLliure() && NovaTecla == 11){
                state = 0;
            }
		break;
		case 3:
  			if (HNouMinut() && NovaTecla != 11) {
				HClearNouMinut();
                LcGotoXY(0,0);
                LcNewString("Current Time");
				state = 2;
			}
			else if (NovaTecla == 11) {
				state = 0;
			}
		break;
	}
}

void MsetNovaTecla(char tecla){
    NovaTecla = tecla;
}