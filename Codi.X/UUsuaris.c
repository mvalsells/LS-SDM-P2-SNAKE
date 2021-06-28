#include <xc.h>
#include "UUsuaris.h"
#define ZERO 0
typedef struct{
    char username[15];
    unsigned char highScore;
}Usuari;
Usuari usuaris[20];
unsigned char numUsuaris = 0;
__bit createUser = 0;
unsigned char quin = 0;
char pos = 0;
__bit findNextUser = 0;
signed char usuariTrobat = -1;
signed char delUser = -1;

void UsersInit(void){
    //NOTA: s'executa un sol cop fora del bucle cooperatiu a la inicialitzacio
    //abans del programa, no afecta a la cooperativitat.
    for(char i = 0; i < 20; i++){
        usuaris[i].username[ZERO] = '\0';
        usuaris[i].highScore = ZERO;
    }
}
void UCancelaNouUser(){
    createUser = ZERO;
   // usuaris[quin].username[0] = '\0';
}

char* UgetUserName(char quin){
    return usuaris[quin].username;
}

char UgetScore(char quin){
    return usuaris[quin].highScore;
}
void UchangeScore(char score){
    usuaris[quin].highScore = score;
}

void UUsuarisNouUsuari(){
    static char state = ZERO;
    switch(state) {
		case 0:
			if (createUser != ZERO && numUsuaris >= 20) {
				createUser = ZERO;
			}
			else if (createUser == 1 && numUsuaris < 20) {
				state++;
			}
			else if (delUser > -1) {
				usuaris[delUser].username[ZERO] = '\0';
				usuaris[delUser].highScore = ZERO;
				state = 2;
			}
		break;
		case 1:
			if (createUser == ZERO) {
				state--;
			}
		break;
		case 2:
			if (usuaris[delUser+1].username[ZERO] != '\0' && delUser < 20) {
				usuaris[delUser] = usuaris[delUser+1];
				delUser++;
			}
			else if (delUser >= 20 /*|| usuaris[delUser+1].username[0] == '\0'*/) {
				delUser = -1;
				state = ZERO;
			}
		break;
	}
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
        createUser = ZERO;
        numUsuaris++;
    }
    
}

char UgetNumUsuaris(void){
    return numUsuaris;
}

signed char UgetUsuariTrobat(void){
    return usuariTrobat;
}

void UtrobaUsuari(void){
    findNextUser = 1;
}

void UdelUser(char index){
    delUser = index;
}