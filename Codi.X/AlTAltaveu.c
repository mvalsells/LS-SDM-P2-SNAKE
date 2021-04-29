void AlTAltaveu.c(void) {
	static char state = 0;

	switch(state) {
		case 0:
			if (reproduir == 1) {
				dobleTicsSemiperiode = 0;
				state = 1;
			}
		break;
		case 1:
			if (TiGetTics(timer_notes) <= notes[i] && reproduir == 1) {
				TiResetTics(timer_notes);
				TRISAbits.A3;
				state = 2;
			}
			else if (reproduir == 0) {
				state = 0;
			}
		break;
		case 2:
			if (TiGetTics(timer_notes) <= dobleTicsSemiperiode) {
				dobleTicsSemiperiode++;
				 if(i > 10) dobleTicsSemiperiode = 0;
				TiResetTics(timer_notes);
				state = 1;
			}
		break;
	}
}