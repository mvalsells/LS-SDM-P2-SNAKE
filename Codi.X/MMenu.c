#include <pic18f4321.h>
#include <xc.h>
#include "MMenu.h"
#include "LcTLCD.h"


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!POTSER SERIA MILLOR HARDCOREJAR-HO per estalviar espai??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SOLS AIXO ES MENJA 40% DE MEMORIA HAHA EATING RAM NO PAPA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char menu0[] = "1. New game\0";
char menu1[] = "2. Show top 5 scores\0";
char menu2[] = "3. Show users\0";
char menu3[] = "4. Modify users\0";
char menu4[] = "5. Show time\0";
char menu5[] = "6. Modify time\0";
char selectUser[] = "1. Select User\0";
char newUser[] = "New User\0";
char enterName[] = "Enter Name:\0";
char highScore[] = "High score: \0";
char enterNewName[] = "Enter New Name\0";
char currentTime[] = "Current Time\0";
char timeFormat[] = "(HH:mm):\0";
char Score[] = "Score: \0";

void printaMenuX(char mostra){
}

void MTInit(){
    //cridar funci� per printar el primer men� amb "mostra=0"
    LcClear();
    //LcPutString(*menu0);
    //LcNewString(menu0);
    //LcNewString(menu1);
    //PutStringCooperatiu();
    
}

void MTMenu(void){   
    static __bit printed=0;
    if (LcEscrivint()==0 && printed==0){
        LcNewString(menu0);
        //printed =1;
    }
}

void yMTMenu(void){
	static char state = 0;
	switch(state) {
		case 0:
			if (LcEscrivint()==0) {
				LcClear();
                LcCursorOff();
                LcGotoXY(1,0);
				LcNewString(menu0);
				state = 1;
			}
		break;
		/*case 1:
			if (LcEscrivint()==0) {
				LcGotoXY(1,1);
				LcNewString(menu1);
				state = 2;
			}
		break;
		case 2:

		break;*/
	}
}
/*/
void xMTMenu(void) {
	static char state = 0;
    static char NovaTecla = 0;
    static char mostra = 0;
    
    
	switch(state) {
		case 0:
			if (NovaTecla == BAIX) {
				if(mostra != 0) mostra--;
				NovaTecla = 0;
				state = 1;
			}
			else if (NovaTecla == AMUNT) {
				if(mostra != 5) mostra++;
				state = 2;
			}
			else if (NovaTecla == ASTERISC && mostra == 0) {
				mostraMenuNewUser();
				state = 3;
			}
			else if (NovaTecla == ASTERISC && mostra == 1) {
				mostraMenuTopScores();
				state = 4;
			}
			else if (NovaTecla == ASTERISC && mostra == 2) {
				mostraMenusShowUsers();
				state = 5;
			}
			else if (NovaTecla == ASTERISC && mostra == 3) {
				mostraMenuModifyUsers();
				state = 6;
			}
			else if (NovaTecla == ASTERISC && mostra == 4) {
				mostraMenuShowTime();
				state = 7;
			}
			else if (NovaTecla == ASTERISC && mostra == 5) {
				mostraMenuModifyTime();
				state = 8;
			}
		break;
		case 1:
			mostraMenu(mostra);
			state = 0;
		break;
		case 2:
			mostraMenu(mostra);
			state = 0;
		break;
		case 3:

		break;
		case 4:

		break;
		case 5:

		break;
		case 6:

		break;
		case 7:

		break;
		case 8:

		break;
	}
}*/