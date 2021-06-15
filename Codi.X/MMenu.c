#include <pic18f4321.h>
#include <xc.h>
#include "MMenu.h"
#include "LcTLCD.h"


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!POTSER SERIA MILLOR HARDCOREJAR-HO per estalviar espai??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SOLS AIXO ES MENJA 40% DE MEMORIA HAHA EATING RAM NO PAPA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//const char menu0[] = "1. New game";
//const char menu1[] = "2. Show top 5 scores";
//const char menu2[] = "3. Show users";
//const char menu3[] = "4. Modify users";
//const char menu4[] = "5. Show time";
//const char menu5[] = "6. Modify time";
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

const char menu[6][21] = {
    "1. New game",
    "2. Show top 5 scores",
    "3. Show users",
    "4. Modify users",
    "5. Show time",
    "6. Modify time"
};

//void MTInit(){  
//}

void MTMenu(void){
	static char state = 0;

	switch(state) {
		case 0:
			if (LcLliure()) {
				LcClear();
				LcCursorOff();
				LcNewString(menu[menuDalt]);
				state = 1;
			}
		break;
		case 1:
			if (LcLliure()) {
				LcPutFletxa();
				LcGotoXY(0,1);
				if(menuDalt != 5) LcNewString(menu[menuDalt+1]);
				state = 2;
			}
		break;
		case 2:
			if (NovaTecla == 2) {
				NovaTecla = -1;
				if(menuDalt > 0) menuDalt--;
				state = 3;
			}
			else if (NovaTecla == 8) {
				NovaTecla = -1;
				if(menuDalt < 5) menuDalt++;
				state = 4;
			}
		break;
		case 3:
			state = 0;
		break;
		case 4:
			state = 0;
		break;
	}
}

void MsetNovaTecla(char tecla){
    NovaTecla = tecla;
}