/*
 * Fan.c
 *
 * Created: 10/25/2023 8:00:54 PM
 * Author : a3abd
 */ 

#include <avr/io.h>
#include "STD_MacRos.h"
#include "ADC.h"
#include "LCD.h"
#include "Timer.h"


int main(void)
{
    LCD_4bit_init();
	ADC_Init();
	Timer0_Fast_PWM_INIT();
	setbit(DDRC,6);//HBridge pins output
	setbit(DDRC,7);
	clrbit(DDRA,0);//temp sensor pin Input
	long long x = 0 , temp = 0;
	int volt = 0 , temprature = 0;
    while (1) 
    {
		x = ADC_Read(0);
		if (x != temp)
		{
			Send_4bit_cmd(0x01);//clear screen
			temp = x;
			volt = (2560 * x) / 1024;
			temprature = volt / 10;
			Send_4bit_string("temprature = ");
			Send_4bit_Number(temprature);
			if (temprature < 25)
			{
				Send_4bit_cmd(0xC0);
				Send_4bit_string("Fan off");
				clrbit(PORTC,6);
				clrbit(PORTC,7);
				Timer0_Set_Duty_Cycle(0);
			}
			else if (temprature >= 25 && temprature < 30)
			{
				Send_4bit_cmd(0xC0);
				Send_4bit_string("Fan on");
				setbit(PORTC,6);
				clrbit(PORTC,7);
				Timer0_Set_Duty_Cycle(0.25);
			}
			
			else if (temprature >= 30 && temprature < 35)
			{
				Send_4bit_cmd(0xC0);
				Send_4bit_string("Fan on");
				setbit(PORTC,6);
				clrbit(PORTC,7);
				Timer0_Set_Duty_Cycle(0.5);
			}
			
			else if (temprature >= 35 && temprature < 40)
			{
				Send_4bit_cmd(0xC0);
				Send_4bit_string("Fan on");
				setbit(PORTC,6);
				clrbit(PORTC,7);
				Timer0_Set_Duty_Cycle(0.75);
			}
			
			else if (temprature >= 40)
			{
				Send_4bit_cmd(0xC0);
				Send_4bit_string("Fan on");
				setbit(PORTC,6);
				clrbit(PORTC,7);
				Timer0_Set_Duty_Cycle(1);
			}
		}
		
    }
}

