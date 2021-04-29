#include "AlTAltaveu.h"
#include "TiTTimer.h"
#include <xc.h>
#include<pic18f4321.h>

char timer_notes;
static __bit reproduir;
static char dobleTicsSemiperiode;



void AlInit(void){
    char timer_notes = TiGetTimer();
    reproduir=0;
    dobleTicsSemiperiode=0;
}

void AlPlayPause(void) {
    reproduir = !reproduir;
}

void AlTAltaveu(void) {
	static char state = 0;
	switch(state) {
		case 0:
			if (reproduir == 1) {
				dobleTicsSemiperiode = 0;
				state = 1;
			}
		break;
		case 1:
			if (TiGetTics(timer_notes) <= dobleTicsSemiperiode && reproduir == 1) {
				TiResetTics(timer_notes);
				TRISAbits.RA3;
				state = 2;
			}
			else if (reproduir == 0) {
				state = 0;
			}
		break;
		case 2:
			if (TiGetTics(timer_notes) <= dobleTicsSemiperiode) {
				dobleTicsSemiperiode++;
				 if(dobleTicsSemiperiode > 10) dobleTicsSemiperiode = 0;
				TiResetTics(timer_notes);
				state = 1;
			}
		break;
	}
}