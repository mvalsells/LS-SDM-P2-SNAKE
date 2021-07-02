#include "HHora.h"
#include <xc.h>
#include "TiTTimer.h"

#define ZERO_CHAR '0'

static char string[6] = "00:00";
static char tempsJugant[] = "00:00";
static unsigned char segons = 0;
static char timerHora = 0;

__bit nouMinut;
__bit estemJugant;
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

void HHoraMotor(void) {
			if (TiGetTics(timerHora) >= 2000) {
				TiResetTics(timerHora);
				segons++;
				nouSegon=1;
				//Segons partida;
				tempsJugant[4]++;
				if(tempsJugant[4] == ('9'+1)){
					tempsJugant[4] = ZERO_CHAR;
					tempsJugant[3]++;
				}
				if(segons >= 60){
                    nouMinut = 1;
					segons = 0;
				  //Miunts rellotge;
					string[4]++;
					if(string[4] == ('9'+1)){
						string[4] = ZERO_CHAR;
						string[3]++;
					}
				}
				//Minuts rellotge;
				if(string[3] == '6'){
					string[4] = ZERO_CHAR;
					string[3] = ZERO_CHAR;
					string[1]++;
					if(string[1] == ('9'+1)){
						string[1] = ZERO_CHAR;
						string[0]++;
					}
				}
				//Minuts partida;
				if(tempsJugant[3] == '6'){
					tempsJugant[4] = ZERO_CHAR;
					tempsJugant[3] = ZERO_CHAR;
					tempsJugant[1]++;
					if(tempsJugant[1] == ('9'+1)){
						tempsJugant[1] = ZERO_CHAR;
						tempsJugant[0]++;
					}
				}
				//Hores relloge;
				if(string[0] >= '2' && string[1] >= '4'){
					string[1] = ZERO_CHAR;
					string[0] = ZERO_CHAR;
				}
			}

}

char* HGetTime(void){    
    return string;
}


char* HTempsJocs(void){
    return tempsJugant;
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

void HJuguem(void){
    estemJugant=1;
    tempsJugant[0] = '0';
    tempsJugant[1] = '0';
    tempsJugant[3] = '0';
    tempsJugant[4] = '0';
}

void HNoJuguem(void){
    estemJugant = 0;
}