#include <pic18f4321.h>
#include <xc.h>
#include "Ssms.h"
#include "TiTTimer.h"
#include "MMenu.h"
#define neg -1

signed char lletraASCII = -1;
char lletraInici[9] = "ADGJMPTW";
char sumaPulsacions = 0;
signed char novaTecla = -1;
signed char timerSMS = -1;
signed char ultimaTecla = -1;
__bit setSMSon = 0;

void Sinit(void){
    timerSMS = TiGetTimer();
}

void SMotor(void) {
	static char state = 0;
	switch(state) {
		case 0:
			if (novaTecla != -1 && setSMSon == 1) {
				TiResetTics(timerSMS);
				state = 3;
			}
			else if (novaTecla == -1 && TiGetTics(timerSMS)>= TSMS && lletraASCII != -1  && setSMSon == 1) {
				MNovaLletra(lletraASCII);
				lletraASCII = neg;
				ultimaTecla = neg;
			}
		break;
		case 1:
			if (novaTecla == ultimaTecla && TiGetTics(timerSMS) < TSMS) {
				novaTecla = neg;
				sumaPulsacions++;
				lletraASCII++;
				state++;
			}
			else if (novaTecla != -1 && novaTecla != ultimaTecla) {
				MNovaLletra(lletraASCII);
				lletraASCII = lletraInici[novaTecla-2];
				ultimaTecla = novaTecla;
				sumaPulsacions = 0;
				novaTecla = neg;
				state--;
			}
		break;
		case 2:
			if (ultimaTecla != 7 && ultimaTecla != 9) {
				state = 5;
			}
			else if (ultimaTecla == 7 || ultimaTecla == 9) {
				state = 6;
			}
		break;
		case 3:
			if (novaTecla > 1 && novaTecla < 10) {
				state = 1;
			}
			else if (novaTecla <= 1 && lletraASCII == -1) {
				MNovaLletra(novaTecla+48);
				novaTecla = neg;
				state = 0;
			}
			else if (novaTecla <= 1 && lletraASCII != -1) {
				MNovaLletra(lletraASCII);
				lletraASCII = neg;
				state++;
			}
		break;
		case 4:
			MNovaLletra(novaTecla+48);
			novaTecla = neg;
			state = 0;
		break;
		case 5:
			if (sumaPulsacions == 4) {
				lletraASCII = lletraInici[ultimaTecla-2];
				sumaPulsacions = 0;
				state = 0;
			}
			else if (sumaPulsacions == 3) {
				lletraASCII = ultimaTecla+48;
				state = 0;
			}
			else if (sumaPulsacions < 3) {
				state = 0;
			}
		break;
		case 6:
			if (sumaPulsacions == 4) {
				lletraASCII = ultimaTecla+48;
				state = 0;
			}
			else if (sumaPulsacions == 5) {
				lletraASCII = lletraInici[ultimaTecla-2];
				sumaPulsacions = 0;
				state = 0;
			}
			else if (sumaPulsacions < 4) {
				state = 0;
			}
		break;
	}
}

void SsetNovaTecla(char tecla){
    novaTecla = tecla;
}

void SMSon(void){
    setSMSon = 1;
    novaTecla = neg;
}

void SMSoff (void){
    setSMSon = 0;
    novaTecla = neg;
}