#include "Switch.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#define PB0123						(*((volatile uint32_t *)0x4000503C))
#define PB0								(*((volatile uint32_t *)0x40005004))
#define PB1								(*((volatile uint32_t *)0x40005008))
#define PB2								(*((volatile uint32_t *)0x40005010))
#define PB3								(*((volatile uint32_t *)0x40005020))



// In handler, read button Data register & assign it to a variable. From then on, read the variable instead of the register,
// 		because reading the register actually clears it.


//**************************************************
// Initializes switches to Port B
// PB0: Play/Pause button
// PB1: Stop/Rewind button
// PB2: Change mode button (instrument change)
//***************************************************
void SwitchesInit(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     // activate clock for Port B
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
	GPIO_PORTB_DIR_R &= ~0x07;				// makes PB0,1,2 in
	GPIO_PORTB_DEN_R |= 0x07;					// enable digital I/O on PB0,1,2
	GPIO_PORTB_IS_R &= ~0x07;					// edge-sensitive
	GPIO_PORTB_IBE_R &= ~0x07;				// not both edges
	GPIO_PORTB_IEV_R &= ~0x07;				// falling edge
	GPIO_PORTB_ICR_R = 0x07;					// clear flags 0,1,2
	GPIO_PORTB_IM_R |= 0x07;					// arm interrupt on PB0,1,2
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF00FF)|0x00004000;		// Port B is priority 2, check to see if we still want priority 2
	NVIC_EN0_R |= 0x02;								// enable interrupt 1 on NVIC
}
