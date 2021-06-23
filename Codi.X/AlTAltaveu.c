#include "AlTAltaveu.h"
#include "TiTTimer.h"
#include <xc.h>

static char timer_nota=PAUSA;
static __bit reproduir=PAUSA;
static char nota=PAUSA;
static char timer_durada=PAUSA;

void AlInit(void){
    timer_nota = TiGetTimer();
    timer_durada = TiGetTimer();
    reproduir=PAUSA;
}

void AlPlay(void) {
    reproduir = PLAY;
}
void AlStop(void) {
    reproduir = PAUSA;
}

void AlTAltaveu(void) {
	static char state = PAUSA;

	switch(state) {
		case 0:
			if (reproduir == PLAY) {
				nota = PLAY;
				TiResetTics(timer_nota);
				TiResetTics(timer_durada);
				state++;
			}
		break;
		case 1:
            
			if (reproduir == PAUSA) {
				state--;
			}
			if (TiGetTics(timer_nota) > nota) {
				LATBbits.LB0 = PLAY;
				TiResetTics(timer_nota);
				state++;
			}
			if (TiGetTics(timer_durada) > DURADA) {
				state = 3;
			}
		break;
		case 2:
			if (TiGetTics(timer_nota) > nota) {
				LATBbits.LB0 = PAUSA;
				TiResetTics(timer_nota);
				state--;
			}
		break;
		case 3:
			TiResetTics(timer_durada);
			nota++;
			if(nota>10){
                nota=PLAY;
            }
            state = PLAY;
		break;
	}
}