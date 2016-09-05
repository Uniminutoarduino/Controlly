/* 
 * File:   user.h
 * Author: Jonathan
 *
 * Created on 7 de octubre de 2015, 09:32 AM
 */

#ifndef USER_H
#define	USER_H

void InitUART1(void);//Config de UART1
void Floattocharsend(float num);//Conversion float to char, next send uart
void inttocharsend(int num);//Conversion int to char, next send uart
void charsend(char *p); //Send text to UART.

#endif	/* USER_H */
