#include <pic18f4321.h>
#include <xc.h>
#include "MMenu.h"
void MTMenu(void) {
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
}
