/*	Author: lab
 *  Partner(s) Name: kgonz
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "scheduler.h"
#include "keypad.h"

#include "io.c"
#endif

enum lcdPrint_states{Init};


//unsigned long int findGCD(unsigned long int a, unsigned long int b)
//{
//	unsigned long c;
//	while(1)
//	{
//		c = a % b;
//		if(c == 0) {return b;}
//		a = b;
//		b = c;
//	}
	
//	return 0;
//}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;
	DDRD = 0xFF;	PORTC = 0x00;

    /* Insert your solution below */

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	const char start = -1;
	task1.state = start;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct =  &LCD_PRINT_TASK;

//	unsigned long GCD = tasks[0]->period;
//	for(unsigned short i = 1; i < numTasks; i++)
//	{
//		GCD = findGCD(GCD, tasks[i]->period);
//	}

	TimerSet(10);
	TimerOn();

	LCD_init();

//	task1.TickFct =  &keypad_tick;

    while (1) {
	
	    for(unsigned short j = 0; j < numTasks; j++)
	    {
		    if(tasks[j]->elapsedTime == tasks[j]->period){
			    tasks[j]->state = tasks[j]->TickFct(tasks[j]->state);
			    tasks[j]->elapsedTime = 0;
		    }

		    tasks[j]->elapsedTime += 1;

	    }
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
    return 0;
}
