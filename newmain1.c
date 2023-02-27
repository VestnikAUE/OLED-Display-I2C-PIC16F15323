#include "CONFIG.h"

void main(void)
{
    TRISC = 0b000000;
    PORTC = 0b011000;
    __delay_ms(1000);
    PORTC = 0b000000;
    
    if (__timeout && __powerdown) PORTC = 0b011000;
    else if (__timeout && !__powerdown) PORTC = 0b010000;
    else if (!__timeout && __powerdown) PORTC = 0b001000;
    __delay_ms(2000);
    PORTC = 0b000000;
    
    i2cBegin();
    
    setupI2C();
    
    beginTransmission(ADDR);
    
    sendControlByte(0x00);
    
    sendCommand(0x26);
    sendCommand(0x00);
    sendCommand(0x05);
    sendCommand(0x00);
    sendCommand(0x07);
    sendCommand(0x2F);
    
    endTransmission();
    
    beginTransmission(ADDR);
    
    sendControlByte(0x40);
    
    for (unsigned char i = 0; i < 8; i++)
        sendCommand(0x01);
    
    endTransmission();
    
    // Test: blinking LEDs program
    /*
    
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    while (1)
    {
        PORTC = 0b000001;
        __delay_ms(2000);
        PORTC = 0b000010;
        __delay_ms(2000);
    }
    */
    return;
}
