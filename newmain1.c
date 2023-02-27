#include "CONFIG.h"

// I have to mention that I run MCU from 5V pins from Arduino Uno. Pins SDA and SCL of display are pulled-up.
void main(void)
{
    // I have two LEDs on pins RC3 and RC4 to check if MCU works.
    TRISC = 0b000000;
    PORTC = 0b011000;
    __delay_ms(1000);
    PORTC = 0b000000;
    
    // Searching through Internet I found some causes to resets - PO and TO bits.
    // Here I am checking them. Also they are negated, so LEDs must light up.
    if (__timeout && __powerdown) PORTC = 0b011000;
    else if (__timeout && !__powerdown) PORTC = 0b010000;
    else if (!__timeout && __powerdown) PORTC = 0b001000;
    __delay_ms(2000);
    // I suppose PIC resets here 'cause LEDs blink with those periods.
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
