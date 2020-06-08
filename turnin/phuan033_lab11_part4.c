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

enum keypad_states{Init, Start};
unsigned char cursor_pos = 0x01;
unsigned char temp_portb = 0x00;
int keypad_tick(int keypad_state)
{
	//unsigned char k = 0x00;
	unsigned char key = 0x00; 
	key = GetKeypadKey();

	switch(keypad_state)
	{
		case Start:
			LCD_DisplayString(1,"Congratulations!");
			keypad_state = Init;
			break;
		case Init:
			keypad_state = Init;
			break;

		default:
			keypad_state = Start;
			break;
	}

	switch(keypad_state)
	{
		case Init:
			
			switch(key)
			{
				case '\0':
                  		//	temp_portb = 0x1F;
                  			break;

				case '0':
					temp_portb = 0x00;
					LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
					break;

                  		case '1':
                  			temp_portb = 0x01;
					LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '2':
                  			temp_portb = 0x02;
					LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '3':
                  			temp_portb = 0x03;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '4':
                  			temp_portb = 0x04;
					LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}

                  			break;

                  		case '5':
                  			temp_portb = 0x05;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '6':
                  			temp_portb = 0x06;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '7':
                  			temp_portb = 0x07;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '8':
                  			temp_portb = 0x08;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}

                  			break;

                  		case '9':
                  			temp_portb = 0x09;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData(temp_portb + '0');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case 'A':
                  			temp_portb = 0x0A;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData('A');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case 'B':
                  			temp_portb = 0x0B;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData('B');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case 'C':
                  			temp_portb = 0x0C;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData('C');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case 'D':
                  			temp_portb = 0x0D;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData('D');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '*':
                  			temp_portb = 0x0E;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData('*');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

                  		case '#':
                  			temp_portb = 0x0F;
                                        LCD_Cursor(cursor_pos);
					LCD_WriteData('#');
					cursor_pos++;
					if(cursor_pos == 17)
					{
						cursor_pos = 1;
					}
                  			break;

				default:
					temp_portb = 0x1B;
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
	DDRD = 0xFF;	PORTD = 0x00;
	DDRC = 0xF0;	PORTC = 0x0F;
    /* Insert your solution below */

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	const char start = -1;
	task1.state = start;
	task1.period = 20;
	task1.elapsedTime = task1.period;
	task1.TickFct =  &keypad_tick;

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
