#include "board.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* System oscillator rate and RTC oscillator rate */
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

/* Set up and initialize clocking prior to call to main */
static void Board_SetupClocking(void)
{
    /* Setup Chip clocking */
    Chip_SetupXtalClocking();

    /* Setup FLASH access to 4 clocks (100MHz clock) */
    Chip_SYSCTL_SetFLASHAccess(FLASHTIM_100MHZ_CPU);
}

/* Set up and initialize hardware prior to call to main */
void Board_SystemInit(void)
{
	Board_SetupClocking();
}
