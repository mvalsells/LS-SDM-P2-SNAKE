#include <xc.h>
#include "CtoA.h"


unsigned char convertir = 250;
char string[] = "000";

void CToAconvertir(unsigned char numero){
    convertir = numero;
}
char* CToAobtenir(void){
    return string;
}
char CToAHaAcabat(void){
    return convertir;
}

void CtoA(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (convertir != 250) {
				string[2]++;
				        if (string[2] == 58) {
				            string[2] = '0';
				            string[1]++;
				        }
				        if (string[1] == 58) {
				            string[1] = '0';
				            string[0]++;
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