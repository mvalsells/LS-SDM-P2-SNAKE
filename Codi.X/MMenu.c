#include <xc.h>
#include "MMenu.h"
#include "GLCDGestioLCD.h"
#include "LcTLCD.h"
#include "HHora.h"
#include "Ssms.h"
#include "UUsuaris.h"
#include "JJoc.h"

#define neg -1

char selectUser[] = "1. Select User";
char newUser[] = "New User";
const char enterName[] = "Enter Name:";
const char highScore[] = "High score:";
const char enterNewName[] = "Enter New Name";
const char currentTime[] = "Current Time";
const char timeFormat[] = "(HH:mm):";
const char Score[] = "Score: ";

unsigned char menuDalt = 0;
signed char NovaTecla = neg;
signed char novaLletra = neg;
char horaTmp[5];
unsigned char pos;
char username[11];


void MTMenu(void){
    static char state = 0;
	switch(state) {
		case 0:
			if (LcLliure()) {
				LcClear();
				SiFerMenu();
				GLCDMostraMenu(menuDalt);
				NovaTecla = neg;
				SMSoff();
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
			else if (NovaTecla == 10 && menuDalt == 5) {
				LcClear();
				NoFerMenu();
				LcNewString("Enter new time");
				state = 11;
			}
			else if (NovaTecla == 10 && menuDalt == 0) {
				NoFerMenu();
				LcClear();
				state = 12;
			}
			else if (NovaTecla == 10 && menuDalt == 4) {
				LcClear();
				NoFerMenu();
				state = 2;
			}
		break;
		case 2:
			if (LcLliure()) {
				LcNewString("Current Time");
				state = 3;
			}
		break;
		case 4:
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
				LcCursorOn();
				state = 5;
			}
		break;
		case 5:
			if (NovaTecla >= 0 && NovaTecla <= 2) {
				horaTmp[0] = NovaTecla+48;
				LcPutChar(horaTmp[0]);
				NovaTecla = neg;
				state = 6;
			}
		break;
		case 6:
			if (NovaTecla >= 0 && NovaTecla <=9) {
				horaTmp[1] = NovaTecla+48;
				LcPutChar(horaTmp[1]);
				NovaTecla = neg;
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
				NovaTecla = neg;
				state = 9;
			}
		break;
		case 9:
			if (NovaTecla >= 0 && NovaTecla <=9) {
				horaTmp[3] = NovaTecla+48;
				LcPutChar(horaTmp[3]);
				NovaTecla = neg;
				state = 10;
			}
		break;
		case 10:
			if (NovaTecla == 10) {
				HActualitzarHora(horaTmp);
				NovaTecla = neg;
				LcCursorOff();
				state = 0;
			}
		break;
		case 3:
			if (LcLliure()) {
				LcGotoXY(0,1);
				LcNewString(HGetTime());
				state = 4;
			}
		break;
		case 12:
			if (LcLliure()) {
				LcNewString("1. Select User");
				state = 13;
			}
		break;
		case 14:
			if (NovaTecla == 1 && UgetNumUsuaris() >= 1) {
				LcClear();
				menuDalt=0;
				NovaTecla = neg;
				state = 20;
			}
			else if (NovaTecla == 2) {
				NovaTecla = neg;
				SMSon();
				LcCursorOn();
				LcClear();
				LcNewString("Enter name:");
				state = 16;
			}
		break;
		case 17:
			if (LcLliure() && novaLletra > 47 && NovaTecla < 10 && UgetNumUsuaris() < 20) {
				LcPutChar(novaLletra);
				NovaTecla = neg;
				UAfegirLletraUsername(novaLletra);
				novaLletra = neg;
				state = 19;
			}
			else if (NovaTecla == 10 && UgetNumUsuaris() < 20) {
				LcCursorOff();
				UAfegirLletraUsername('\0');
				SMSoff();
				LcClear();
				state = 24;
			}
			else if (NovaTecla == 11 || UgetNumUsuaris() >= 20) {
				LcCursorOff();
				UCancelaNouUser();
				state = 0;
			}
		break;
		case 20:
			if (LcLliure()) {
				LcClear();
				LcPutFletxa();
				LcGotoXY(3,0);
				LcNewString(UgetUserName(menuDalt));
				NovaTecla = neg;
				state = 23;
			}
		break;
		case 19:
			if (LcLliure()) {
				state = 17;
			}
		break;
		case 24:
			if (LcLliure()) {
				NovaTecla = neg;
				LcNewString(UgetUserName(menuDalt));
				JJuguem(menuDalt);
				HJuguem();
				state = 25;
			}
		break;
		case 13:
			if (LcLliure()) {
				LcGotoXY(0,1);
				LcNewString("2. New User");
				NovaTecla = neg;
				state = 14;
			}
		break;
		case 16:
			if (LcLliure()) {
				LcGotoXY(0,1);
				pos = 0;
				UcreateUser();
				state = 17;
			}
		break;
		case 21:
			if (NovaTecla == 8) {
				if (menuDalt<UgetNumUsuaris()-1) menuDalt++;
				state = 20;
			}
			else if (NovaTecla == 2) {
				if (menuDalt>0) menuDalt--;
				state = 20;
			}
			else if (NovaTecla == 11) {
				NovaTecla = neg;
				menuDalt = 0;
				state = 0;
			}
			else if (NovaTecla == 10) {
				LcClear();
				state = 24;
			}
		break;
		case 23:
			if (LcLliure()) {
				LcGotoXY(3,1);
				if(menuDalt+2 <= UgetNumUsuaris()) LcNewString(UgetUserName(menuDalt+1));
				state = 21;
			}
		break;
		case 25:
			if (JUsuari() == neg) {
				HNoJuguem();
				state = 0;
			}
		break;
	}
}

void MsetNovaTecla(char tecla){
    NovaTecla = tecla;
}

void MNovaLletra(char lletra){
    novaLletra = lletra;
}