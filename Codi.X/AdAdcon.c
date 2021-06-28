#include <xc.h>
#include <pic18f4321.h>
#include "JJoc.h"
#include "LcTLCD.h"

char valorADC = 127;
char lastState = 0;
__bit borram = 0;

void AdInit(void){
    ADCON0 = 0x01;//00000001 chA //000001_1 chB
    ADCON1 = 0x0D;//00001101
    ADCON2 = 0x09;//00001110
    ADRESH = 127;
}
void AdMotor(void) {
	static char state = 0;
    switch(state) {
		case 0:
			if (ADCON0bits.GODONE == 0) {
                borram = 1;
				valorADC = ADRESH;
				state = 1;
			}
		break;
		case 1:
			if (valorADC > 150) {
				JnovaTecla(2);
				ADCON0 = 0x03;
				state = 2;
			}
			else if (valorADC < 100) {
				JnovaTecla(8);
				ADCON0 = 0x03;
				state = 2;
			}
			else if (valorADC < 150 && valorADC > 100) {
				ADCON0=0x07;
				state = 4;
			}
		break;
		case 2:
			if (ADCON0bits.GODONE==0) {
				borram = 0;
                valorADC = ADRESH;
				state = 3;
			}
		break;
		case 3:
			if (valorADC > 150 || valorADC < 100) {
				ADCON0 = 0x03;
				state = 2;
			}
			else if (valorADC < 150 && valorADC > 100) {
				ADCON0 = 0x07;
				state = 4;
                borram = 0;
			}
		break;
		case 4:
			if (ADCON0bits.GODONE==0) {
				valorADC = ADRESH;
				state = 5;
			}
		break;
		case 5:
			if (valorADC > 150) {
				JnovaTecla(6);
				ADCON0=0x07;
				state = 6;
			}
			else if (valorADC < 100) {
				JnovaTecla(4);
				ADCON0=0x07;
				state = 6;
			}
			else if (valorADC < 150 && valorADC > 100) {
				ADCON0=0x03;
				state = 0;
			}
		break;
		case 6:
			if (ADCON0bits.GODONE==0) {
				valorADC = ADRESH;
				state = 7;
			}
		break;
		case 7:
			if (valorADC > 150 || valorADC < 100) {
				ADCON0=0x07;
				state = 6;
			}
			else if (valorADC < 150 && valorADC > 100) {
				ADCON0=0x03;
				state = 0;
			}
		break;
	}
}