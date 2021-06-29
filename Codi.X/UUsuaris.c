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
unsigned char quin = 0;
char pos = 0;
__bit findNextUser = 0;
signed char usuariTrobat = -1;
signed char delUser = -1;

unsigned char top5indexs[] = {-1, -1, -1, -1, -1};

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

char UgetUserNameChar(char quin, char pos){
    return usuaris[quin].username[pos];
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

void UMotorUsuaris(){
    static char state = ZERO;
    switch(state) {
		case 0:
			if (createUser != 0 && numUsuaris >19) {
				createUser = 0;
			}
			else if (createUser == 1 && numUsuaris < 20) {
				state++;
			}
			else if (delUser > -1) {
				usuaris[delUser].username[0] = '\0';
				usuaris[delUser].highScore = 0;
				if(top5indexs[0] == delUser){
                    top5indexs[0] = top5indexs[1];
                    top5indexs[1] = top5indexs[2];
					top5indexs[2] = top5indexs[3];
					top5indexs[3] = top5indexs[4];
					top5indexs[4] = -1;
				}else if(top5indexs[1] == delUser){
					top5indexs[1] = top5indexs[2];
					top5indexs[2] = top5indexs[3];
					top5indexs[3] = top5indexs[4];
					top5indexs[4] = -1;
				}else if(top5indexs[2] == delUser){
					top5indexs[2] = top5indexs[3];
					top5indexs[3] = top5indexs[4];
					top5indexs[4] = -1;
				}else if(top5indexs[3] == delUser){
					top5indexs[3] = top5indexs[4];
					top5indexs[4] = -1;
				}else if(top5indexs[4] == delUser){
					top5indexs[4] = -1;
				}
				state = 2;
			}
		break;
		case 1:
			if (createUser == 0) {
				state--;
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
        pos = ZERO;
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
    numUsuaris--;
    
}
void UeditUsername(char menuDalt, char pos, char novaLletra){
    usuaris[menuDalt].username[pos] = novaLletra;
    if(novaLletra = '\0') pos = 0;//si ens falta espai de flash, fer serivr una var nova "pos = pos2" pq sigui local
}