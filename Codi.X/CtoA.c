#include <xc.h>
#include "CtoA.h"

unsigned char convertir = 250;
char stringScore[] = "000";

void CToAConverteix(unsigned char numero){
    convertir = numero;
}
char* CToAobtenir(void){
    return stringScore;
}
char CToAHaAcabat(void){
    return convertir;
}

void CToAReset(void){
    stringScore[0] = '0';
    stringScore[1] = '0';
    stringScore[2] = '0';
}

void CtoA(void) {
	static char state = 0;
    switch(state){
		case 0:
			if (convertir != 250) {
				stringScore[2]++;
				        if (stringScore[2] == 58) {
				            stringScore[2] = '0';
				            stringScore[1]++;
				        }
				        if (stringScore[1] == 58) {
				            stringScore[1] = '0';
				            stringScore[0]++;
				        }
				        convertir--;
				state = 1;
			}
		break;
		case 1:
			if (convertir == 0) {
				convertir = 250;
				state = 0;
			}
			else if (convertir > 0) {
				state = 0;
			}
		break;
    }
}