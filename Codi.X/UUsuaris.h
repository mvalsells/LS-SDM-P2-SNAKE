#ifndef UUsuaris_
#define UUsuaris_

void UUsuarisNouUsuari(void);
char* UgetUserName(char quin);
char UgetScore(char quin);
void UdelUser(char quin);
void UsersInit(void);
void UcreateUser(void );
void UAfegirLletraUsername(char lletra);
char UgetNumUsuaris(void);
void UCancelaNouUser(void);
void UchangeScore(char score);

void UeditUsername(char menuDalt, char pos, char novaLletra);
#endif