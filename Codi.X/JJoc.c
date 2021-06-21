#include "JJoc.h"
#include <xc.h>
#include "AdAdcon.h"
#include "HHora.h"

__bit fiJoc = 0;
signed char joguem = -1;
char novaDireccio = 0;

__bit JFiJoc(void){
    return fiJoc;
}


void JMotor(void){
    
}


void JJoguem(char usuari){
    joguem = usuari;
}
void JnovaTecla(char direccio){
    novaDireccio = direccio;
}