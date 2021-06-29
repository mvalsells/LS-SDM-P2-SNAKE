//BY La Salle.
#ifndef LCD_H
#define LCD_H
#include <xc.h>


#define SetD4_D7Sortida()		(TRISCbits.TRISC0 = TRISCbits.TRISC1 = TRISCbits.TRISC2 = TRISCbits.TRISC3 = 0)
#define SetD4_D7Entrada()		(TRISCbits.TRISC0 = TRISCbits.TRISC1 = TRISCbits.TRISC2 = TRISCbits.TRISC3 = 1)
#define SetControlsSortida()    (TRISCbits.TRISC5 = TRISDbits.TRISD7 = TRISCbits.TRISC4 = 0)
#define SetD4(On)				(LATCbits.LATC0 = (On))
#define SetD5(On)				(LATCbits.LATC1 = (On))
#define SetD6(On)				(LATCbits.LATC2 = (On))
#define SetD7(On)				(LATCbits.LATC3 = (On))
#define GetBusyFlag()           (PORTCbits.RC3)
#define RSUp()					(LATCbits.LATC5 = 1)
#define RSDown()				(LATCbits.LATC5 = 0)
#define RWUp()					(LATDbits.LATD7 = 1)
#define RWDown()				(LATDbits.LATD7 = 0)
#define EnableUp()				(LATCbits.LATC4 = 1)
#define EnableDown()            (LATCbits.LATC4 = 0)

#define CURSORSHIFT 0x10
#define MOVELEFT 0x00
#define DISPLAYMOVE 0x08
// -------------------------------END--HARDWARE---AREA--------------------


void LcInit(char rows, char columns);
// Pre: Rows = {1, 2, 4}  Columns = {8, 16, 20, 24, 32, 40 }
// Pre: There is a free timer
// Pre: It needs 40ms of tranquility between the VCC raising and this constructor being called.
// Post: This routine can last up to 100ms
// Post: The display remains cleared, the cursor turned off and at the position 0, 0.

void LcEnd(void);
// The destructor

void LcScroll(void);
// Pre: Data saved to the ram in order to shift it
// Post: Shifts all the rows to the left in a ciclic way

void LcClear(void);
// Post: Clears the display and sets the cursor to its previous state. 
// Post: The next order can last up to 1.6ms. 

void LcCursorOn(void);
// Post: Turn on the cursor
// Post: The next order can last up to 40us. 

void LcCursorOff(void);
// Post: Turns off the cursor
// Post: The next order can last up to 40us. 

void LcGotoXY(char Column, char Row);
// Pre : Column between 0 and 39, row between 0 and 3. 
// Post: Sets the cursor to those coordinates. 
// Post: The next order can last up to 40us. 

void LcPutChar(char c);
// Post: Paints the char in the actual cursor position and increments 
// its position. If the column gets to 39 it returns to 0.
// The row of the LCD is increased when this happens until the second
// row and then it is reset back to row 0 if it has 2 rows total. 
// If the LCD has 4 rows it will reset back to row 0 when it
// reaches row 4 and the columns will go till 39 before reseting to 0.
// The one row LCDs returns to 0 when a column gets to 39. 
// The row is never increased. 
	// The char is written

void LcPutStringDebug(char *s);
void LcNewString(char new_s[]);
void PutStringCooperatiu();
void LcPutFletxa();
void LcLCD();
__bit LcLliure(void);
void LcInsertFletxa(void);
#endif