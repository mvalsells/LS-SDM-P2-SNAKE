#ifndef TITTIMER_H_
#define TITTIMER_H_

void TiInitTimer(void);
//Pre: --
//Post: Initializes the timer0 to interrupt each 1ms.

void TiResetTics(char Handle);
//Pre: 0<Handle<MAXTIMERS.
//Post: Writes in the tics of the Handle timer the universal tics of the system.

int TiGetTics(char Handle);
//Pre: 0<Handle<MAXTIMERS.
//Post: Less than 32767 tics have passed since the last TiResetTics.
//Post: Returns the number of tics from the last TiResetTics for the Handle timer.

char TiGetTimer(void);
//Pre: There are free timers.
//Post: Returns the Handler of a timer and marks it as busy.
//Post:	If there are not free timers left, returns a -1.

void TiFreeTimer (char Handle);
//Pre: 0<Handle<MAXTIMERS.
//Post: The Handle timer is marked as free.

void  _TiRSITimer (void);


#endif