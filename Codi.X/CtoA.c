#include <xc.h>
#include "CtoA.h"

unsigned char convertir = 250;
char stringScore[] = "000";
__bit borram = 0;

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
    if (convertir != 250) {
				if (convertir != 0){
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
				} else {
					convertir = 250;
				}
    }
}