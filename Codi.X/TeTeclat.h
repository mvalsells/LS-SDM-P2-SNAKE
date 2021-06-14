#ifndef TETECLAT_H_
#define TETECLAT_H_

/*#define Col1 PORTDbits.RD4
#define Col2 PORTDbits.RD5
#define Col3 PORTDbits.RD6*/
#define Col1 LATDbits.LD4
#define Col2 LATDbits.LD5
#define Col3 LATDbits.LD6
#define TREBOT 32 //16 ms

void TeInit();
void TeTeclat();

#endif