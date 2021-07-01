#include <xc.h>
#include "UUsuaris.h"
#define ZERO 0
#define NUMUSERS 20
typedef struct{
    char username[11];
    unsigned char highScore;
}Usuari;
Usuari usuaris[NUMUSERS];
unsigned char numUsuaris = 0;
__bit createUser = 0;
char pos = 0;
__bit findNextUser = 0;
signed char usuariTrobat = -1;
signed char delUser = -1;
__bit calcTop = 0;
char j;
char cops;

signed char top5indexs[] = {2, -1, -1, -1, -1};

char UgetScore(char quin){
    return usuaris[quin].highScore;
}

void UCancelaNouUser(){
    createUser = ZERO;
   // usuaris[quin].username[0] = '\0';
}

char* UgetUserName(char quin){
    return usuaris[quin].username;
}

void UchangeScore(char quin, char score){
    usuaris[quin].highScore = score;
}

void UMotorUsuaris(){
    static char state = ZERO;
    	switch(state) {
		case 0:
			if (createUser != 0 && numUsuaris >19) {
				createUser = 0;
			}
			else if (createUser == 1 && numUsuaris < 20) {
				state = 1;
			}
			else if (delUser > -1) {
				usuaris[delUser].username[0] = '\0';
				usuaris[delUser].highScore = 0;
				state = 2;
			}
			else if (0) {
				j = 0;
				state = 3;
			}
		break;
		case 1:
			if (createUser == 0) {
				state = 0;
			}
		break;
		case 2:
			if (usuaris[delUser+1].username[0] != '\0' && delUser < 20) {
				usuaris[delUser] = usuaris[delUser+1];
				delUser++;
			}
			else if (delUser >= 20 /*|| usuaris[delUser+1].username[0] == '\0'*/) {
				delUser = -1;
				state = 0;
			}
		break;
		case 3:
			if(UgetScore(j) > UgetScore(top5indexs[0])){
				top5indexs[0] = j;
			}
			j++;
			state = 4;
		break;
		case 4:
			if (j<numUsuaris) {
				state = 3;
			}
			else if (j == numUsuaris && numUsuaris > 1) {
				j=0;
				cops = 1;
				state = 5;
			}
			else if (j == numUsuaris && numUsuaris == 1) {
				state = 0;
                calcTop = 0;
			}
		break;
		case 5:
			if(UgetScore(j) > UgetScore(top5indexs[cops]) && UgetScore(j) <= UgetScore(top5indexs[cops-1]) && j !=top5indexs[cops-1] ){
				top5indexs[cops] = j;
			}
			j++;
			state = 6;
		break;
		case 6:
			if (j<numUsuaris) {
				state = 5;
			}else if ((cops == 5 && j == numUsuaris) || numUsuaris-1 == cops) {
                calcTop = 0;
				state = 0;
			}
			else if (j == numUsuaris && cops < 5 && cops < numUsuaris) {
				j=0;
				cops++;
				state = 5;
			}
			
		break;
	}
}

void UcalcTop5(void){
    calcTop = 1;
}
__bit UHaAcabatCalcTop5(void){
    return 0;
}
signed char UgetTop5(char quin){
    return top5indexs[quin];
}

void UcreateUser(void ){
    createUser = 1;
}
void UAfegirLletraUsername(char lletra){
	if(createUser) usuaris[numUsuaris].username[pos]=lletra;
	if (lletra != '\0'){
        pos++;
    }else{
        usuaris[numUsuaris].username[pos] = '\0';
        pos = ZERO;
        createUser = ZERO;
        numUsuaris++;
    }
}

char UgetNumUsuaris(void){
    return numUsuaris;
}

//signed char UgetUsuariTrobat(void){
//    return usuariTrobat;
//}

//void UtrobaUsuari(void){
//    findNextUser = 1;
//}

void UdelUser(char index){
    delUser = index;
    numUsuaris--;
}
void UeditUsername(char menuDalt, char pos, char novaLletra){
    usuaris[menuDalt].username[pos] = novaLletra;
    if(novaLletra == '\0') pos = 0;//si ens falta espai de flash, fer serivr una var nova "pos = pos2" pq sigui local
}