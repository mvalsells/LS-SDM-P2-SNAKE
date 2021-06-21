#include "HHora.h"
#include <xc.h>
#include "TiTTimer.h"
static char string[5] = "00:00";
static char tempsJugant[5] = "00:00";
static unsigned char segons = 0;
static char timerHora = 0;

__bit nouMinut;
__bit estemJugant();
__bit nouSegon;

__bit HNouMinut(void){
    return nouMinut;
}

void HClearNouMinut(void){
    nouMinut = 0;
}

void HInit(void){
    timerHora = TiGetTimer();
    TiResetTics(timerHora);
    nouMinut = 0;
}

void HHoraMotor(void) { //comentat (minutsAscii) -> en variables tmp
                        //sense comentar (string[]) -> directmaent a la string
    static char state = 0;
	switch(state) {
		case 0:
			if (TiGetTics(timerHora) >= 2000) {
				TiResetTics(timerHora);
				segons++;
				if(segons >= 60){
					segons = 0;
				  //Segons partida;
				  tempsJugant[4]++;
				  if(tempsJugant[4] == ('9'+1)){
				    tempsJugant[4] = '0';
				    tempsJugant[3]++;
				  }
				  //Miunts rellotge;
					string[4]++;
					if(string[4] == ('9'+1)){
						string[4] = '0';
						string[3]++;
					}
				}
				//Minuts rellotge;
				if(string[3] == '6'){
					string[4] = '0';
					string[3] = '0';
					string[1]++;
					if(string[1] == ('9'+1)){
						string[1] = '0';
						string[0]++;
					}
				}
				//Minuts partida;
				if(tempsJugant[3] == '6'){
					tempsJugant[4] = '0';
					tempsJugant[3] = '0';
					tempsJugant[1]++;
					if(tempsJugant[1] == ('9'+1)){
						tempsJugant[1] = '0';
						tempsJugant[0]++;
					}
				}
				//Hores relloge;
				if(string[0] >= '2' && string[1] >= '4'){
					string[1] = '0';
					string[0] = '0';
				}
				state = 1;
			}
		break;
		case 1:
			if(estemJugant == 0){ 
                tempsJugant[0] = '0';
                tempsJugant[1] = '0';
                tempsJugant[3] = '0';
                tempsJugant[4] = '0';
            };
			state = 0;
		break;
	}
}

char* HGetTime(void){    
    return string;
}

void HActualitzarHora(char nova[]){
    string[0] = nova[0];
    string[1] = nova[1];
    string[3] = nova[2];
    string[4] = nova[3];
}

__bit HNouSegon(void){
    return nouSegon;
}

void HClearNouSegon(void){
    nouSegon = 0;
}