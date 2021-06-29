#include <xc.h>
#include "JJoc.h"

char ultimaTeclaAD = 0;

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
			if (ADCON0bits.GODONE == 0 && ADRESH < 200 && ADRESH > 50) {
				ADCON0 = 0x07;
				state++;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH >= 200) {
				if(ultimaTeclaAD != 2)JnovaTecla(2);
				ultimaTeclaAD = 2;
				ADCON0 = 0x07;
				state++;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH <= 50) {
				if(ultimaTeclaAD != 8)JnovaTecla(8);
				ultimaTeclaAD = 8;
				ADCON0 = 0x07;
				state++;
			}
		break;
		case 1:
			if (ADCON0bits.GODONE == 0 && ADRESH < 200 && ADRESH > 50) {
				ADCON0 = 0x03;
				state--;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH >= 200) {
				if(ultimaTeclaAD != 6)JnovaTecla(6);
				ultimaTeclaAD = 6;
				ADCON0 = 0x03;
				state--;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH <= 50) {
				if(ultimaTeclaAD != 4)JnovaTecla(4);
				ultimaTeclaAD = 4;
				ADCON0 = 0x03;
				state--;
			}
		break;
	}
}