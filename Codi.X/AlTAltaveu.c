#include "AlTAltaveu.h"
#include "TiTTimer.h"
#include <xc.h>
#include<pic18f4321.h>

static char timer_nota;
static __bit reproduir;
static char nota;
static char timer_durada;

void AlInit(void){
    char timer_nota = TiGetTimer();
    char timer_durada = TiGetTimer();
    reproduir=0;
    reproduir = 0;
}

void AlPlay(void) {
    reproduir = 1;
}
void AlStop(void) {
    reproduir = 0;
}

void AlTAltaveu(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (reproduir == 1) {
				state = 1;
                nota = 1;
			}
		break;
		case 1:
            if (TiGetTics(timer_durada) >= 100) {
				state = 3;
			}
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
				state = 1;
			}
		break;
		case 3:
			TiResetTics(timer_durada);
			nota++;
			if(nota>10)nota=1;
			state = 1;
		break;
	}
}