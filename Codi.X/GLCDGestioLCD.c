#include <xc.h>
#include "TiTTimer.h"
#include "LcTLCD.h"
#include "GLCDGestioLCD.h"
const char menu[][22] = {
    "1. New game",
    "2. Show top 5 scores ",
    "3. Show users",
    "4. Modify users",
    "5. Show time",
    "6. Modify time"
};

char timerGLCD=0;
char menuDaltGLCD=0;
__bit ferMenu = 0;
__bit newString = 0;

void SiFerMenu(void){
    ferMenu = 1;
}
void NoFerMenu(void){
    ferMenu = 0;
}

void GLCDInit(void){
    timerGLCD=TiGetTimer();
}

void GLCDMostraMenu(unsigned char num){
    newString = 1;
    menuDaltGLCD = num;
    ferMenu = 1;
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
			if (length1 < 17 && ferMenu == 1) {
				LcGotoXY(0,0);
				LcNewString(menu[menuDaltGLCD]);
				state = 5;
			}
			else if (length1 >= 17 && ferMenu == 1) {
				state++;
			}
		break;
		case 3:
			if (j>=16) {
				min1++;
				max1++;
				if (menu[menuDaltGLCD][max1] == '\0') max1=0;
				if (menu[menuDaltGLCD][min1] == '\0') min1=0;
				j=0;
				k1=min1;
				state = 6;
			}
			else if (j<16) {
				LcGotoXY(j,0);
				LcPutChar(menu[menuDaltGLCD][k1]);
				j++;
				k1++;
				if(menu[menuDaltGLCD][k1] == '\0') k1 = 0;
			}
		break;
		case 6:
			if (menuDaltGLCD<5) {
				LcPutFletxa();
				state++;
			}
			else if (menuDaltGLCD >= 5) {
				LcPutFletxa();
				state = 0;
			}
		break;
		case 5:
			if (LcLliure() && menuDaltGLCD<5) {
				LcPutFletxa();
				state = 7;
			}
			else if (LcLliure() && menuDaltGLCD >= 5) {
				LcPutFletxa();
				state = 0;
			}
		break;
		case 0:
			if (newString != 0 && ferMenu == 1) {
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
				state++;
			}
		break;
		case 1:
			if (menu[menuDaltGLCD][length1] == '\0' && menuDaltGLCD>=5) {
				state++;
			}
			else if (menu[menuDaltGLCD][length1] != '\0') {
				length1++;
			}
			else if (menuDaltGLCD<5 && menu[menuDaltGLCD][length1] == '\0') {
				state = 13;
			}
		break;
		case 7:
			if (length2 < 17 && ferMenu == 1) {
				LcGotoXY(0,1);
				LcNewString(menu[menuDaltGLCD+1]);
				state++;
			}
			else if (length2 >= 17 && ferMenu == 1) {
				state = 9;
			}
		break;
		case 9:
			if (j<16) {
				LcGotoXY(j,1);
				LcPutChar(menu[menuDaltGLCD+1][k2]);
				j++;
				k2++;
				if(menu[menuDaltGLCD+1][k2] == '\0') k2 = 0;
			}
			else if (j>=16) {
				min2++;
				max2++;
				if (menu[menuDaltGLCD+1][max2] == '\0') max2=0;
				if (menu[menuDaltGLCD+1][min2] == '\0') min2=0;
				j=0;
				k2=min2;
				state++;
			}
		break;
		case 11:
			if (TiGetTics(timerGLCD)>= 2000 && newString == 0 && ferMenu == 1) {
				LcClear();
				state = 2;
			}
			else if (newString != 0 && ferMenu == 1) {
				LcClear();
				state = 0;
			}
		break;
		case 10:
			TiResetTics(timerGLCD);
			state++;
		break;
		case 8:
			if (LcLliure()) {
				TiResetTics(timerGLCD);
				state = 11;
			}
		break;
		case 13:
			if (menu[menuDaltGLCD+1][length2] != '\0') {
				length2++;
			}
			else if (menu[menuDaltGLCD+1][length2] == '\0' ) {
				state = 2;
			}
		break;
	}
}