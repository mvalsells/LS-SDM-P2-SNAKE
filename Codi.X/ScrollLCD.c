#include <xc.h>
#include "LcTLCD.h"
#include "TiTTimer.h"

char text[4][7] = {
	"ABCDEF",
	"GHIJKL",
	"MNOPKR",
	"STUVWX"
};

char pos = 0;
char menuDalt = 0;
char timerScroll;

void ScInit(void){
    timerScroll = TiGetTimer();
}

void ScScroll(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (LcLliure()) {
				LcGotoXY(0,0);
				LcNewString(text[menuDalt]);
				menuDalt++;
				state = 1;
			}
		break;
		case 1:
			if (LcLliure()) {
				LcGotoXY(0,1);
				LcNewString(text[menuDalt]);
				menuDalt++;
				state = 2;
			}
		break;
		case 2:
			if (LcLliure()) {
				LcGotoXY(16,0);
				LcNewString(text[menuDalt]);
				menuDalt++;
				TiResetTics(timerScroll);
				state = 5;
			}
		break;
		case 3:
			if (TiGetTics(timerScroll) > 1250) {
				state = 4;
			}
		break;
		case 4:
			if (pos<16) {
				TiResetTics(timerScroll);
				LcScroll();
				pos++;
				state = 3;
			}
			else if (pos>15) {
				menuDalt = 0;
				state = 0;
			}
		break;
		case 5:
			if (LcLliure()) {
				LcGotoXY(16,1);
				LcNewString(text[menuDalt]);
				menuDalt++;
				TiResetTics(timerScroll);
				state = 3;
			}
		break;
	}
}