#ifndef HHORA_
#define HHORA_

void HInit(void);
void HHoraMotor(void);
char* HGetTime(void);
__bit HNouMinut(void);
void HClearNouMinut(void);
void HActualitzarHora(char nova[]);
#endif