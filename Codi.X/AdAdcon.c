#include "MMenu.h"
#include <xc.h>
#include <pic18f4321.h>



void AdInit(void){
    ADCON0 = 0x01;//000000_1 chA //000001_1 chB
    ADCON1 = 0x0D;//00001101
    ADCON2 = 0x0E;//0000111  
}
void AdMotor(void) {
	static char state = 0;
	switch(state) {
		case 0:
			if (ADCON0bits.GODONE == 0 && ADRESH < 200 && ADRESH > 50) {
				ADCON0 = 0x07;
				state = 1;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH >= 200) {
				//JnovaTecla(2);
                MsetNovaTecla(2); //DEBUG
				ADCON0 = 0x07;
				state = 1;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH <= 50) {
				//JnovaTecla(8);
                MsetNovaTecla(8); //DEBUG
				ADCON0 = 0x07;
				state = 1;
			}
		break;
		case 1:
			if (ADCON0bits.GODONE == 0 && ADRESH < 200 && ADRESH > 50) {
				ADCON0 = 0x03;
                state = 0;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH >= 200) {
				//JnovaTecla(6);
                MsetNovaTecla(6); //DEBUG
				ADCON0 = 0x03;
				state = 0;
			}
			else if (ADCON0bits.GODONE == 0 && ADRESH <= 50) {
                //JnovaTecla(4);
				MsetNovaTecla(4); //DEBUG
				ADCON0 = 0x03;
				state = 0;
			}
		break;
	}
}