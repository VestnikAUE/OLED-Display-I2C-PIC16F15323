#ifndef _FUNCS_H
#define	_FUNCS_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ 32000000

void setArr(unsigned char* arr, unsigned char c, unsigned char size);
void copyArr(unsigned char* dest, unsigned char* source, unsigned char ssize);
void concatenateArrs(unsigned char* first, unsigned char* second, unsigned char size1, unsigned char size2);
unsigned char* numToArr(unsigned char num, unsigned char size);
unsigned char twoPower(unsigned char i);
void errSignal();

#endif	/* XC_HEADER_TEMPLATE_H */

