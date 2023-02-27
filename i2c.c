#include "i2c.h"

void checkAck()
{
    SSP1CON2bits.ACKEN = 1;
    SSP1CON2bits.ACKDT = 0;
    while (SSP1CON3bits.ACKTIM);
    SSP1IF = 0;
    if (!SSP1CON2bits.ACKSTAT)
    {
        if (SSP1CON2bits.ACKDT)
        {
            PORTCbits.RC0 = 1;
            __delay_ms(500);
        }
        else PORTCbits.RC0 = 0;
    }
    else if (SSP1CON2bits.ACKSTAT || SSP1CON1bits.WCOL)
    {
        while (1)
            errSignal();
    }
//    checkInterrupt();
    PORTCbits.RC0 = 0;
    SSP1IF = 0;
}

void i2cBegin()
{
//    TRISCbits.TRISC3 = 0;
//    TRISCbits.TRISC4 = 0;
//    ANSELCbits.ANSC3 = 0;
//    ANSELCbits.ANSC4 = 0;
//    PORTCbits.RC3 = 1;
//    PORTCbits.RC4 = 1;
//    TRISCbits.TRISC3 = 1;
//    TRISCbits.TRISC4 = 1;
//    ODCONCbits.ODCC3 = 1;
//    ODCONCbits.ODCC4 = 1;
    SSP1CON1bits.SSPM = 0b1000;  //
    SSP1ADD = 0x13;
    SSP1CON3bits.SCIE = 0;
    SSP1CON3bits.PCIE = 0;
    SSP1CON1bits.SSPEN = 1; // enable I2C
    SSP1CON3bits.SDAHT = 0; // minimum 100 ns SDA pin hold time
//    RC0PPS = 0x16; // set RC3 pin to SDA
    SSP1DATPPS = 0x10;
//    RC1PPS = 0x15; // set RC4 pin to SCL
    SSP1CLKPPS = 0x11;
}

void beginTransmission(unsigned char addr)
{
    SSP1CON2bits.SEN = 1;
    __delay_ms(1);
    SSP1BUF = addr;
    SSP1IF = 0;
    while (SSP1STATbits.BF) PORTCbits.RC1 = 1;
    SSP1IF = 0;
    checkAck();
    PORTCbits.RC1 = 0;
}

// Data stream = 0x40
// Single data byte = 0xC0
// Single command byte = 0x80
// Command stream = 0x00
void sendControlByte(unsigned char mode) // dorc = 0 => DATA ONLY (d-or-c = data or command)
{
    SSP1BUF = mode;
    SSP1IF = 0;
    while (SSP1STATbits.BF) PORTCbits.RC1 = 1;
    SSP1IF = 0;
    checkAck();
    PORTCbits.RC1 = 0;
}

void sendCommand(unsigned char command)
{
    SSP1BUF = command;
    __delay_ms(1);
    SSP1IF = 0;
    while (SSP1STATbits.BF) PORTCbits.RC1 = 1;
    SSP1IF = 0;
    checkAck();
    PORTCbits.RC1 = 0;
}

void sendCommandwD(unsigned char command, unsigned char data)
{
    SSP1BUF = command;
    __delay_ms(1);
    SSP1IF = 0;
    while (SSP1STATbits.BF) PORTCbits.RC1 = 1;
    SSP1IF = 0;
    checkAck();
    PORTCbits.RC1 = 0;
    
    SSP1BUF = data;
    __delay_ms(1);
    SSP1IF = 0;
    while (SSP1STATbits.BF) PORTCbits.RC1 = 1;
    SSP1IF = 0;
    checkAck();
    PORTCbits.RC1 = 0;
}

void sendCommandw2D(unsigned char command, unsigned char data1, unsigned char data2)
{    
    SSP1BUF = command;
    __delay_ms(50);
    SSP1BUF = 0;
    
    checkAck();
        
    SSP1BUF = data1;
    __delay_ms(50);
    SSP1BUF = 0;    
    
    checkAck();
    
    SSP1BUF = data2;
    __delay_ms(50);
    SSP1BUF = 0;    
    
    checkAck();
}

void endTransmission() // initiates STOP condition
{
    SSP1CON2bits.PEN = 1;
    __delay_ms(1);
    SSP1IF = 0;
}

void setupI2C()
{
    beginTransmission(ADDR);
    /*
    sendControlByte(0x00);
//    sendCommand(0xAE);         // set display off
    sendCommandwD(0xA8, 0x3F); // set MUX ratio
    sendCommandwD(0xD3, 0x00); // set display offset
    sendCommand(0x40);         // set display start line
    sendCommand(0xA0);         // set segment re-map
    sendCommand(0xC0);         // set COM output scan direction
    sendCommandwD(0xDA, 0x02); // set COM pins hardware configuration
//    sendCommandwD(0xDB, 0x20, 1); // set vcomh deselect level
    sendCommandwD(0x81, 0x7F); // set contrast control 
    sendCommand(0xA4);         // disable entire display on
    sendCommand(0xA7);         // set normal display
    sendCommandwD(0xD5, 0x80); // set oscillator frequency
    sendCommandwD(0x8D, 0x14); // enable charge pump regulator
    sendCommand(0xAF);         // set display on
    
//    startCondition(1);
    */
    sendControlByte(0x00);
    sendCommand(0xAE);         // set display off
    sendCommandwD(0xD5, 0x80); // set oscillator frequency
    sendCommandwD(0xA8, 0x3F); // set MUX ratio
    sendCommandwD(0xD3, 0x00); // set display offset
    sendCommand(0x40);         // set display start line
    sendCommandwD(0x8D, 0x14); // enable charge pump regulator
    sendCommand(0xA1);         // set segment re-map
    sendCommand(0xC0);         // set COM output scan direction
    sendCommandwD(0xDA, 0x12); // set COM pins hardware configuration
    sendCommandwD(0x81, 0xCF); // set contrast control 
    sendCommandwD(0xD9, 0xF1); // set pre-changed period
    sendCommandwD(0xDB, 0x40); // set vcomh deselected level
    sendCommand(0xA5);         // set entire display off
    sendCommand(0xA6);         // set normal display
    sendCommandwD(0x20, 0x00); // set memory addressing mode
    sendCommand(0xAF);         // set display on
        
    endTransmission();
}