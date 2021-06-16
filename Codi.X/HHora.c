#include "HHora.h"
#include <pic18f4321.h>
#include <xc.h>
#include "TiTTimer.h"
static char string[6] = "??:??";
//static unsigned char horesAscii1 = '0';
//static unsigned char horesAscii2 = '0';
//static unsigned char minutsAscii1 = '0';
//static unsigned char minutsAscii2 = '0';
static unsigned char segons = 0;
static char timerHora = 0;

__bit nouMinut = 0;

__bit HNouMinut(void){
    return nouMinut;
}

void HClearNouMinut(void){
    nouMinut = 0;
}

void HInit(void){
    timerHora = TiGetTimer();
    TiResetTics(timerHora);
}

void HHoraMotor(void) { //comentat (minutsAscii) -> en variables tmp
                        //sense comentar (string[]) -> directmaent a la string
    static char state = 0;
	switch(state) {
		case 0:
			if (TiGetTics(timerHora) >= 20) {//2000
				TiResetTics(timerHora);
				segons++;
				if(segons >= 60){
                    nouMinut = 1;
					segons = 0;
					
					//minutsAscii1++;
                    string[4]++;
					if(/*minutsAscii1*/ string[5] == ('9'+1)){
						//minutsAscii1 = '0';
                        string[4] = '0';
						//minutsAscii2++;
                        string[3]++;
					}
				}
				if(/*minutsAscii2*/ string[3] == '6'){
					
					//minutsAscii1 = '0';
                    string[4] = '0';
					//minutsAscii2 = '0';
                    string[3] = '0';
					
					//horesAscii1++;
                    string[1]++;
					if(/*horesAscii1*/ string[1] == ('9'+1)){
						//horesAscii1 = '0';
                        string[1] = '0';
						//horesAscii2++;
                        string[0]++;
					}
				}
				if(/*horesAscii2*/ string[0] >= '2' && /*horesAscii1*/ string[1] >= '4'){
					
					//horesAscii1 = '0';
                    string[1] = '0';
					//horesAscii2 = '0';
                    string[0] = '0';
				}
				state = 0;
			}
		break;
	}
}

char* HGetTime(void){
//    string[0] = horesAscii2;
//    string[1] = horesAscii1;
//    
//    string[3] = minutsAscii2;
//    string[4] = minutsAscii1;
    
    return string;
}

void HActualitzarHora(char nova[]){
    string[0] = nova[0];
    string[1] = nova[1];
    string[3] = nova[2];
    string[4] = nova[3];
}