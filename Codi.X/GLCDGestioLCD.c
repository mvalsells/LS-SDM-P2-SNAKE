#ifndef GLCD_C_
#define GLCD_C_
#include <xc.h>
#include "TiTTimer.h"
#include "LcTLCD.h"
const char menu[7][22] = {
    "1. New game",
    "2. Show top 5 scores ",
    "3. Show users",
    "4. Modify users",
    "5. Show time",
    "6. Modify time"
};

char timerGLCD=0;
char menuDalt=0;
__bit newString = 0;

void GLCDInit(void){
    timerGLCD=TiGetTimer();
}

void GLCDMostraMenu(unsigned char num){
    newString = 1;
    menuDalt = num;
}

void GLCDMotor(void) {
	static char state = 0;
    static char j=0;
    static char max1 = 15;
    static char min1 = 0;
    static char min2 = 0;
    static char max2 = 15;
    static char k1 = 0;
    static char k2 = 0;
    static char length1=0;
    static char length2=0;
    switch(state) {
		case 2:
			if (length1 < 17) {
				LcGotoXY(0,0);
				LcNewString(menu[menuDalt]);
				state = 5;
			}
			else if (length1 >= 17) {
				state = 3;
			}
		break;
		case 3:
			if (j>=16) {
				min1++;
				max1++;
				if (menu[menuDalt][max1] == '\0') max1=0;
				if (menu[menuDalt][min1] == '\0') min1=0;
				j=0;
				k1=min1;
				state = 6;
			}
			else if (j<16) {
				LcGotoXY(j,0);
				LcPutChar(menu[menuDalt][k1]);
				j++;
				k1++;
				if(menu[menuDalt][k1] == '\0') k1 = 0;
				state = 3;
			}
		break;
		case 6:
			if (menuDalt<5) {
				LcPutFletxa();
				state = 7;
			}
			else if (menuDalt >= 5) {
				LcPutFletxa();
				state = 11;
			}
		break;
		case 5:
			if (LcLliure() && menuDalt<5) {
				LcPutFletxa();
				state = 7;
			}
			else if (LcLliure() && menuDalt >= 5) {
				LcPutFletxa();
				state = 0;
			}
		break;
		case 0:
			if (newString != 0) {
				length1 = 0;
				length2 = 0;
				LcGotoXY(0,0);
				min1 = 0;
				max1 = 15;
				min2 = 0;
				max2 = 15;
				j = 0;
				k1 = 0;
				k2 = 0;
				newString = 0;
				state = 1;
			}
		break;
		case 1:
			if (menu[menuDalt][length1] == '\0' && menuDalt>=5) {
				state = 2;
			}
			else if (menu[menuDalt][length1] != '\0') {
				length1++;
			}
			else if (menuDalt<5 && menu[menuDalt][length1] == '\0') {
				state = 13;
			}
		break;
		case 7:
			if (length2 < 17) {
				LcGotoXY(0,1);
				LcNewString(menu[menuDalt+1]);
				state = 8;
			}
			else if (length2 >= 17) {
				state = 9;
			}
		break;
		case 9:
			if (j<16) {
				LcGotoXY(j,1);
				LcPutChar(menu[menuDalt+1][k2]);
				j++;
				k2++;
				if(menu[menuDalt+1][k2] == '\0') k2 = 0;
				state = 9;
			}
			else if (j>=16) {
				min2++;
				max2++;
				if (menu[menuDalt+1][max2] == '\0') max2=0;
				if (menu[menuDalt+1][min2] == '\0') min2=0;
				j=0;
				k2=min2;
				state = 10;
			}
		break;
		case 11:
			if (TiGetTics(timerGLCD)>= 2000 && newString == 0) {
				LcClear();
				state = 2;
			}
			else if (newString != 0) {
				LcClear();
				state = 0;
			}
		break;
		case 10:
			TiResetTics(timerGLCD);
			state = 11;
		break;
		case 8:
			if (LcLliure()) {
				TiResetTics(timerGLCD);
				state = 11;
			}
		break;
		case 13:
			if (menu[menuDalt+1][length2] != '\0') {
				length2++;
			}
			else if (menu[menuDalt+1][length2] == '\0' ) {
				state = 2;
			}
		break;
	}
}
#endif