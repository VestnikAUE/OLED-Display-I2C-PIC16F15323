#ifndef _I2C_H
#define	_I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "funcs.h"

#define ADDR 0b01111000
#define WIDTH 128
#define HEIGHT 32

void checkAck();
void i2cBegin();
void beginTransmission(unsigned char addr);
void sendControlByte(unsigned char mode);
void sendCommand(unsigned char command);
void sendCommandwD(unsigned char command, unsigned char data);
void sendCommandw2D(unsigned char command, unsigned char data1, unsigned char data2);
void setupI2C();
void endTransmission();

#endif

