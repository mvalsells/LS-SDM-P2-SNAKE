#include "TeTeclat.h"
#include "TiTTimer.h"
#include "MMenu.h"
#include <xc.h>
#include <pic18f4321.h>
#include "Ssms.h"
#include "JJoc.h"

static char tiTeclat=0;

char teclaPremuda[4][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {10,0,11}
};

void TeInit(void){
    tiTeclat=TiGetTimer();
}

void TeTeclat(void) {
	static char state = 0;
    static char cols=0;
    static char files = 0;
    files = PORTDbits.RD0 + PORTDbits.RD1*2 + PORTDbits.RD2*3 + PORTDbits.RD3*4;
	switch(state) {
		case 0:
			if (files==0) {
				Col1=1;
				Col2=0;
				Col3=0;
				cols=0;
				state++;
			}
			else if (files!=0) {
				TiResetTics(tiTeclat);
				state = 3;
			}
		break;
		case 1:
			if (files==0) {
				Col1=0;
				Col2=1;
				Col3=0;
				cols=1;
				state++;
			}
			else if (files!=0) {
				TiResetTics(tiTeclat);
				state = 3;
			}
		break;
		case 2:
			if (files==0) {
				Col1=0;
				Col2=0;
				Col3=1;
				cols=2;
				state = 0;
			}
			else if (files!=0) {
				TiResetTics(tiTeclat);
				state++;
			}
		break;
		case 3:
			if (TiGetTics(tiTeclat)>=TREBOT) {
				state++;
			}
		break;
		case 4:
			if (files==0) {
				state = 1;
			}
			else if (files!=0) {
                MsetNovaTecla(teclaPremuda[files-1][cols]);
                SsetNovaTecla(teclaPremuda[files-1][cols]);
                JnovaTecla(teclaPremuda[files-1][cols]);
				state++;
			}
		break;
		case 5:
			if (files==0) {
				TiResetTics(tiTeclat);
				state++;
			}
		break;
		case 6:
			if (TiGetTics(tiTeclat)>=TREBOT) {
				state++;
			}
		break;
		case 7:
			if (files!=0) {
				state = 5;
			}
			else if (files==0) {
				state = 0;
			}
		break;
	}
}

/*char teclaPremuda(char col, char files){
    return 0;
}*/