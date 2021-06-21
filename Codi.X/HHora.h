#ifndef HHORA_
#define HHORA_

void HInit(void);
void HHoraMotor(void);
char* HGetTime(void);
__bit HNouMinut(void);
void HClearNouMinut(void);
void HActualitzarHora(char nova[]);
__bit HNouSegon(void);
void HClearNouSegon(void);
void HJuguem(void);
void HNoJuguem(void);
char* HTempsJocs(void);
#endif