/*
 * LCD.c
 *
 * Created: 9/9/2023 4:47:24 PM
 *  Author: a3abd
 */ 
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include "STD_MacRos.h"
#include "LCD.h"

void Send_4bit_Number(int data)
{
	int i=0,digits=0;
	char arr[10];
	
	while (data != 0)
	{
		arr[i]=data%10;
		i++;
		data=data/10;
		digits++;
	}
	
	for(i=digits-1 ; i>=0 ; i--)
	{
		Send_4bit_Char(arr[i]+48); 
	}
	
}

void Send_4bit_Char(char data)
{
    PORTA = (PORTA & 0x0F) | (data & 0xF0); 
	setbit(PORTB,RS); // Send Data
	clrbit(PORTB,RW); // Write Data
	setbit(PORTB,En); // For the LCD to take the data
	_delay_ms(10);
	clrbit(PORTB,En); // To make LCD display the sent data
	PORTA = (PORTA & 0x0F) | (data << 4); 
	_delay_ms(10);
	setbit(PORTB,En);
	_delay_ms(10);
	clrbit(PORTB,En);
}

void LCD_4bit_init()
{
	DDRA |= 0xF0;
	setbit(DDRB,RS);
	setbit(DDRB,RW);
	setbit(DDRB,En);
	_delay_ms(20);
	Send_4bit_cmd(0x02);// return home
	Send_4bit_cmd(0x28);// 2 line and 4 bit mode
	Send_4bit_cmd(0x0E);// display on
	Send_4bit_cmd(0x06);// auto increment
	Send_4bit_cmd(0x01);// clear screen
	_delay_ms(20);
}

void Send_4bit_cmd(char cmd)
{
	PORTA = (PORTA & 0x0F) | (cmd & 0xF0);
	clrbit(PORTB,RS); // Send cmd
	clrbit(PORTB,RW); // Write cmd
	setbit(PORTB,En); // For the LCD to take the cmd
	_delay_ms(1);
	clrbit(PORTB,En); // To make LCD display the sent cmd
	PORTA = (PORTA & 0x0F) | (cmd << 4); 
	_delay_ms(1);
	setbit(PORTB,En);
	_delay_ms(1);
	clrbit(PORTB,En);
	_delay_ms(20);
}

void Send_4bit_string(char *ptr)
{
	int i=0;
	while(ptr[i] != 0)
	{
		Send_4bit_Char(ptr[i]);
		i++;
	}
}