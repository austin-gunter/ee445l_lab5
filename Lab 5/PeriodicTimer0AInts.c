// PeriodicTimer0AInts.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// oscilloscope or LED connected to PF3-1 for period measurement
// When using the color wheel, the blue LED on PF2 is on for four
// consecutive interrupts then off for four consecutive interrupts.
// Blue is off for: dark, red, yellow, green
// Blue is on for: light blue, blue, purple, white
// Therefore, the frequency of the pulse measured on PF2 is 1/8 of
// the frequency of the Timer0A interrupts.

#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "Timer0A.h"
#include "DAC.h"
#include "Switch.h"
#include "Timer1A.h"
#include "Music.h"

extern const unsigned short Trumpet64[];
extern const unsigned short Bassoon64[];
extern const unsigned short Oboe64[];

extern uint32_t NoteArray[];
extern uint32_t LengthArray[];
uint32_t ArrayIndex = 0;
uint32_t InstrumentIndex = 0;
uint32_t Mode = 0;							// 0 = trumpet, 1 = bassoon, 2 = oboe
uint32_t PlayFlag = 0;
uint32_t Debug = 0;


#define EF 804   // 311.127 Hz			
#define F 716   // 349.228 Hz			
#define G 638   // 391.995 Hz			
#define AF 602   // 415.305 Hz			
#define BF 536   // 466.164 Hz			
#define C 478   // 523.251 Hz			
#define DF1 451   // 554.365 Hz			
#define EF1 402   // 622.254 Hz
#define EigthNote 3478261 

// Timer0A Handler = note frequency
void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout
  TIMER0_TAILR_R = 16000000/(NoteArray[ArrayIndex]*64);    // 4) reload value
	if(Mode == 0){
		DAC_Out(Trumpet64[InstrumentIndex%64]);	
	}
	else if(Mode == 1){
		DAC_Out(Bassoon64[InstrumentIndex%64]);	
	}
	else if(Mode == 2){
		DAC_Out(Oboe64[InstrumentIndex%64]);	
	}
	InstrumentIndex ++;
	Debug++;
}


// Timer1A Handler = note length timer
void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
	ArrayIndex ++;
	if(ArrayIndex == 57){
	  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A
		TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A
		PlayFlag = 0;
		ArrayIndex = 0;
		InstrumentIndex = 0;
	}
	else{
		TIMER1_TAILR_R = (LengthArray[ArrayIndex]*EigthNote);
		TIMER0_TAILR_R = 0;
	}
}

void GPIOPortB_Handler(void){

//*************Play/Pause Button********************//
	if(GPIO_PORTB_RIS_R&0x01){
		GPIO_PORTB_IM_R &= ~0x01;		// Mask interrupt
		GPIO_PORTB_ICR_R = 0x01;		// Acknowledge/Clear flag
		if(PlayFlag == 0){
			PlayFlag = 1;
			Timer0A_Init(16000000/(NoteArray[0]*64));
			Timer1A_Init(LengthArray[0]*EigthNote);
		}
		else{
			GPIO_PORTB_IM_R |= 0x01;
			uint32_t TempReload = TIMER1_TAILR_R;
			while((GPIO_PORTB_RIS_R&0x01) == 0){
				// Stop & Rewind Button while paused
				if(GPIO_PORTB_RIS_R&0x02){
					GPIO_PORTB_IM_R &= ~0x02;		// Mask interrupt
					GPIO_PORTB_ICR_R = 0x02;		// Acknowledge/Clear flag
					TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A
					TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A
					PlayFlag = 0;
					ArrayIndex = 0;
					InstrumentIndex = 0;
					GPIO_PORTB_IM_R |= 0x02;		// Re-arm interrupt
					break;
				}
				// Mode Button while paused
				else if(GPIO_PORTB_RIS_R&0x04){
					GPIO_PORTB_IM_R &= ~0x04;		// Mask interrupt
					GPIO_PORTB_ICR_R = 0x04;		// Acknowledge/Clear flag
					Mode ++;
					if(Mode >= 3){
						Mode = 0;
					}
					GPIO_PORTB_IM_R |= 0x04;
				}
			}
			GPIO_PORTB_ICR_R = 0x01;		// Acknowledge/Clear flag
			TIMER1_TAILR_R = TempReload;
		}
		GPIO_PORTB_IM_R |= 0x01;
	}
//*************Stop/Rewind Button****************//
	else if(GPIO_PORTB_RIS_R&0x02){
		GPIO_PORTB_IM_R &= ~0x02;		// Mask interrupt
		GPIO_PORTB_ICR_R = 0x02;		// Acknowledge/Clear flag
	  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A
		TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A
		PlayFlag = 0;
		ArrayIndex = 0;
		InstrumentIndex = 0;
		GPIO_PORTB_IM_R |= 0x02;		// Re-arm interrupt
	}
//***************Mode Button*****************//
	else if(GPIO_PORTB_RIS_R&0x04){
		GPIO_PORTB_IM_R &= ~0x04;		// Mask interrupt
		GPIO_PORTB_ICR_R = 0x04;		// Acknowledge/Clear flag
		Mode ++;
		if(Mode >= 3){
			Mode = 0;
		}
		GPIO_PORTB_IM_R |= 0x04;
	}
}

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F16HZ (50000000/16)
#define F20KHZ (50000000/20000)
//debug code
int main(void){ 
  PLL_Init(Bus16MHz);              // bus clock at 16 MHz
	DACinit();
	SwitchesInit();
//  Timer0A_Init(F16HZ);  // initialize timer0A (16 Hz)
  EnableInterrupts();

  while(1){
    WaitForInterrupt();
  }
}

