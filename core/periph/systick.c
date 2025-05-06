#include <systick.h>
#include <nvic.h>

void systick_init(void) {
	SYSTICK.csr = SYST_ENABLE | SYST_TICKINT;
	SYSTICK.rvr = SYST_TOP;
	/* so systick should have the lowest priority of all interrupts, this
	 * crashes the code though... */
	// NVIC_IPR3 = (0xffU << 24);
}
