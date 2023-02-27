#include "funcs.h"

void setArr(unsigned char* arr, unsigned char c, unsigned char size) // memset clone
{ 
    for (unsigned char i = 0; i < size; i++)
        arr[i] = c;
}

void copyArr(unsigned char* dest, unsigned char* source, unsigned char ssize) // strcpy clone
{
    for (unsigned int i = 0; i < ssize; i++) dest[i] = source[i];
}

void concatenateArrs(unsigned char* first, unsigned char* second, unsigned char size1, unsigned char size2) // strcat clone
{
    unsigned char i = 0;
    for (i; i < size1; i++)
    {
    	if (first[i] > 1) break;
    }
    
    if (i == size1 - 1 || size1-i < size1-size2)
    {
    	while (1) { errSignal(); };
    }
    
    unsigned char k = 0;
    for (unsigned char j = i; j < size2+i; j++)
    {
    	first[j] = second[k];
    	k++;
    }
}

unsigned char* numToArr(unsigned char num, unsigned char size)
{
    static unsigned char buffer[8];
    setArr(buffer, 0, size);
    if (num > twoPower(size)-1) return 0;
    else
    {
        unsigned char i = 0;
        while (num > 0)
        {
            buffer[size-i-1] = (num % 2 == 1);
            num = (unsigned char)(num / 2);
            i += (unsigned char)1;
        }
    }
    return buffer;
}

unsigned char twoPower(unsigned char i) // pow(2, i) clone
{
    unsigned char ret = 1;
    for (unsigned char j = 0; j < i; j++) ret *= 2;
    return ret;
}

//void setPin(unsigned char pin, unsigned char inout, unsigned char cls)
//{
//    TRISC = 0b111111;
//    if (cls == 'c')
//    {
//        if (!inout) TRISC += twoPower(pin);
//        else TRISC -= twoPower(pin);
//    }
//    else if (cls == 'a')
//    {
//        if (!inout) TRISA += twoPower(pin);
//        else TRISA -= twoPower(pin);
//    }
//}

void errSignal()
{
    TRISC = 0b000000;
    PORTC = 0b000011;
    __delay_ms(1000);
    PORTC = 0b000000;
    __delay_ms(1000);
}
