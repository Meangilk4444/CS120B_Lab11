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
#endif

enum keypad_states{Init};

int keypad_tick(int keypad_state)
{
	//unsigned char k = 0x00;
	unsigned char key = 0x00; 
	key = GetKeypadKey();

	switch(keypad_state)
	{
		case Init:
			keypad_state = Init;
			break;

		default:
			keypad_state = Init;
			break;
	}

	switch(keypad_state)
	{
		case Init:
			
			switch(key)
			{
				case '\0':
                  			PORTB = 0x1F;
                  			break;

				case '0':
					PORTB = 0x00;
					break;

                  		case '1':
                  			PORTB = 0x01;
                  			break;

                  		case '2':
                  			PORTB = 0x02;
                  			break;

                  		case '3':
                  			PORTB = 0x03;
                  			break;

                  		case '4':
                  			PORTB = 0x04;
                  			break;

                  		case '5':
                  			PORTB = 0x05;
                  			break;

                  		case '6':
                  			PORTB = 0x06;
                  			break;

                  		case '7':
                  			PORTB = 0x07;
                  			break;

                  		case '8':
                  			PORTB = 0x08;
                  			break;

                  		case '9':
                  			PORTB = 0x09;
                  			break;

                  		case 'A':
                  			PORTB = 0x0A;
                  			break;

                  		case 'B':
                  			PORTB = 0x0B;
                  			break;

                  		case 'C':
                  			PORTB = 0x0C;
                  			break;

                  		case 'D':
                  			PORTB = 0x0D;
                  			break;

                  		case '*':
                  			PORTB = 0x0E;
                  			break;

                  		case '#':
                  			PORTB = 0x0F;
                  			break;

				default:
					PORTB = 0x1B;
					break;
			}
	break;
	}

	return keypad_state;
}

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
	DDRC = 0xF0;	PORTC = 0x0F;
    /* Insert your solution below */

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	const char start = -1;
	task1.state = start;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct =  &keypad_tick;

	unsigned long GCD = tasks[0]->period;
	for(unsigned short i = 1; i < numTasks; i++)
	{
		GCD = findGCD(GCD, tasks[i]->period);
	}

	TimerSet(GCD);
	TimerOn();

    while (1) {
	
	    for(unsigned short j = 0; j < numTasks; j++)
	    {
		    if(tasks[j]->elapsedTime == tasks[j]->period){
			    tasks[j]->state = tasks[j]->TickFct(tasks[j]->state);
			    tasks[j]->elapsedTime = 0;
		    }
		    tasks[j]->elapsedTime += GCD;
	    }
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
    return 0;
}
