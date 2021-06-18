#include <xc.h>
#include "UUsuaris.h"

typedef struct{
    char username[11];
    unsigned char highScore;
}Usuari;
Usuari usuaris[20];
unsigned char numUsuaris = 0;
__bit createUser = 0;
char *newUsername;
unsigned char quin = 0;
unsigned char i = 0;
char pos = 0;

void UsersInit(void){
    //NOTA: s'executa un sol cop fora del bucle cooperatiu a la inicialitzacio
    //abans del programa, no afecta a la cooperativitat.
    for(char i = 0; i < 20; i++){
   //     usuaris[i].username[0] = '\0';
    }
}

char* getUserName(char quin){
    return usuaris[quin].username;
}

char getScore(char quin){
    return usuaris[quin].highScore;
}

void delUser(char quin){
    usuaris[quin].username[0] = '\0';
}

void UUsuarisNouUsuari(){
    static char state = 0;
    switch(state) {
		case 0:
			if (createUser == 1 && numUsuaris < 20) {
				quin = 0;
				state = 1;
			}
			else if (createUser != 0 && numUsuaris >= 20) {
				createUser = 0;
			}
		break;
		case 1:
			if (usuaris[quin].username[0] == '\0') {
				numUsuaris++;
				pos=0;
				state = 2;
			}
			else if (usuaris[quin].username[0] != '\0') {
				quin++;
			}
		break;
		case 2:
			if (usuaris[quin].username[pos] == '\0') {
				createUser = 0;
				state = 0;
			}
			else if (usuaris[quin].username[pos] != '\0') {
			}
		break;
	}
}

void UcreateUser(void ){
    createUser = 1;
}
void UAfegirLletraUsername(char lletra){
	usuaris[quin].username[pos]=lletra;
	if (lletra != '\0') pos++;
}