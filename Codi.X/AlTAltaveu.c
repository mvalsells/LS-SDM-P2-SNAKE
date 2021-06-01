#include "AlTAltaveu.h"
#include "TiTTimer.h"
#include <xc.h>
#include <pic18f4321.h>

static char timer_nota=0;
static __bit reproduir=0;
static char nota=0;
static char timer_durada=0;
static char patata=10;

void AlInit(void){
    timer_nota = TiGetTimer();
    timer_durada = TiGetTimer();
    reproduir=0;
}

void AlPlay(void) {
    reproduir = 1;
}
void AlStop(void) {
    reproduir = 0;
}
/*
void AlTAltaveu(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (reproduir == 1) {
				nota = 5;
				TiResetTics(timer_nota);
				TiResetTics(timer_durada);
				state = 1;
			}
		break;
		case 1:
			if (reproduir == 0) {
				state = 0;
			}
			else if (TiGetTics(timer_nota) >= nota) {
				LATBbits.LB0 = 1;
				TiResetTics(timer_nota);
				state = 2;
			}
		break;
		case 2:
			if (TiGetTics(timer_nota) >= nota) {
				LATBbits.LB0 = 0;
				TiResetTics(timer_nota);
				state = 3;
			}
		break;
		case 3:
			if (TiGetTics(timer_durada) >= DURADA) {
                state = 4;
			} else {
				state = 1;
			}
		break;
		case 4:
			TiResetTics(timer_durada);
			nota++;
			 if(nota>10) {
                 nota=1;
             }
			state = 1;
		break;
	}
}*/

void AlTAltaveu(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (reproduir == 1) {
				nota = 1;
				TiResetTics(timer_nota);
				TiResetTics(timer_durada);
				state = 1;
			}
		break;
		case 1:
            
			if (reproduir == 0) {
				state = 0;
			}
			else if (TiGetTics(timer_nota) >= nota) {
				LATBbits.LB0 = 1;
				TiResetTics(timer_nota);
				state = 2;
			}
			if (TiGetTics(timer_durada) >= DURADA) {
				state = 3;
			}
		break;
		case 2:
			if (TiGetTics(timer_nota) >= nota) {
				LATBbits.LB0 = 0;
				TiResetTics(timer_nota);
				state = 1;
			}
		break;
		case 3:
			TiResetTics(timer_durada);
			nota++;
			if(nota>10){
                nota=1;
            }
            state = 1;
		break;
	}
}