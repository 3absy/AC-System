/*
 * LCD.h
 *
 * Created: 9/9/2023 4:47:09 PM
 *  Author: a3abd
 */ 

#ifndef LCD_H_
#define LCD_H_

#define RS 1
#define RW 2
#define En 0

void Send_4bit_Char(char data);
void LCD_4bit_init();
void Send_4bit_cmd(char cmd);
void Send_4bit_string(char *ptr);
void Send_4bit_Number(int data);


#endif /* LCD_H_ */