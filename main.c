/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F15323
        Driver Version    :  2.00
*/

//#include <pic16f15323.h>
#include "CONFIG.h"

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

//#include "../Charger.X/I2C.h"

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/EEPROM_app.h"
//
//
#define DISPLAY_ADDR 0x3C
//#define MEMORY_ADDR 0x50
//#define MCP23008_REG_ADDR_IODIR 0x00
//#define MCP23008_REG_ADDR_GPIO 0x09
//#define PINS_DIGITAL_OUTPUT 0x00
//#define PINS_DIGITAL_LOW 0x00
//#define PINS_DIGITAL_HIGH 0xFF
/*
                         Main application
 */

//static unsigned char poses[15] = 
//{
//    0xC0, // one_down2
//    0x30, // one_down1
//    0xF0, // two_down
//    0x0C, // one_up2
//    0xCC, // one_up_down2
//    0x3C, // two_mid
//    0xFC, // three_down
//    0x03, // one_up1
//    0xC3, // one_up_down3
//    0x33, // one_up_down1
//    0xF3, // three_sep_1
//    0x0F, // two_up
//    0xCF, // three_sep_2
//    0x3F, // three_up
//    0xFF // four
//};

//static uint8_t array[26] = {0x00,       // send control byte (command stream)
//    0xAE,       // set display off
//    0xD5, 0x80, // set display clock divide ratio/oscfreq 
//    0xA8, 0x3F, // set multiplex ratio
//    0xD3, 0x00, // set display offset
//    0x40,       // set display start line
//    0x8D, 0x14, // set charge pump
//    0xA1,       // set segment re-map
//    0xC0,       // set COM output scan direction
//    0xDA, 0x12, // set COM pins hardware configuration
//    0x81, 0xCF, // set contrast control
//    0xD9, 0xF1, // set pre-changed period
//    0xDB, 0x40, // set vcomh deselected level
//    0xA4,       // set entire display off
//    0xA6,       // set normal display
//    0x20, 0x00, // set memory addressing mode (horizontal)
//    0xAF        // set display on
//};
//

//////
//////

////
static unsigned char adrs[12][3] = 
{
    {0, 0, 18},
    {72, 0, 8},
    {104, 0, 12},
    {152, 0, 11},
    {196, 0, 13},
    {0, 1, 13},
    {52, 1, 17},
    {120, 1, 9},
    {156, 1, 19},
    {0, 2, 15},
    {60, 2, 30},
    {0, 3, 24}
};
//
static unsigned char i = 0;
static unsigned char buff[2] = {0xC0, 0x00};
static unsigned char list[26];

static void initialize_oled()
{
    list[0] = 0x00;
    for (unsigned char i = 1; i < 26; i++)
    {
        EEPROM_ReadBlock(4, i, &list[i], 1);
//        __delay_ms(1);
    }
    I2C1_WriteNBytes(DISPLAY_ADDR, list, 26);
    unsigned char ret[7] = {0x00, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x7};
    I2C1_WriteNBytes(DISPLAY_ADDR, ret, 7);
//    buff[1] = 0x00;
}

static void clearGDDRAM()
{
    for (unsigned short i = 0; i < 128*8; i++)
        I2C1_WriteNBytes(DISPLAY_ADDR, buff, 2);
}

//
static void drawNumber(unsigned char* num)
{
    i = 0;
    unsigned char array[2][3][4];
    unsigned char iter1 = 0;
    unsigned char iter2 = 0;    
    initialize_oled();
//    __delay_ms(100);
    clearGDDRAM();
    unsigned char k = 0;
    unsigned char l = 0;
    unsigned char j = 0;
    unsigned char count[2];
    for (unsigned char n = 0; n < 8; n++)
    {
        for (i = 0; i < 3-(adrs[*num][2]-iter1<3)*(3-adrs[*num][2]+iter1); i++)
        {
            EEPROM_ReadBlock(adrs[*num][1], adrs[*num][0]+(i+iter1)*4, &array[0][i], 4);
//            __delay_ms(1);
        }
        for (i = 0; i < 3-(adrs[*(num+1)][2]-iter2<3)*(3-adrs[*(num+1)][2]+iter2); i++)
        {            
            EEPROM_ReadBlock(adrs[*(num+1)][1], adrs[*(num+1)][0]+(i+iter2)*4, &array[1][i], 4);
//            __delay_ms(1);
            array[1][i][0] += 16;
            array[1][i][1] += 16;
        }
        count[0] = 1; count[1] = 1;
        for (i = 0; i < 2; i++)
        {
            if (array[i][0][2] == array[i][1][2] && array[i][0][2] == array[i][2][2]) count[i] = 3;
            else if (array[i][0][2] == array[i][1][2]) count[i] = 2;
        }
        iter1 += count[0];
        iter2 += count[1];
        for (i = 0; i < 2; i++)
            for (j = 0; j < count[i]; j++)
            {
                while (k < array[i][j][0] || l != array[i][j][2])
                {
                    I2C1_WriteNBytes(DISPLAY_ADDR, buff, 2);
                    k++;
                    if (k == 128)
                    {
                        k = 0;
                        l++;
                    }
                }
                EEPROM_ReadBlock(5, array[i][j][3], &buff[1], 1);
                __delay_ms(1);
//                buff[1] = poses[array[i][j][3]];
                while (k <= array[i][j][1] && l == array[i][j][2])
                {
                    I2C1_WriteNBytes(DISPLAY_ADDR, buff, 2);
                    k++;
                    if (k == 128)
                    {
                        k = 0;
                        l++;
                    }
                }
                buff[1] = 0x00;
            }
        for (i = 0; i < 2; i++)
            for (j = 0; j < 3; j++)
                for (unsigned char m = 0; m < 4; m++)
                    array[i][j][m] = 0;
    }
}

//static unsigned char array[15][4] = { {51, 51, 0, 6},
//		{52, 60, 0, 3},
//		{61, 61, 0, 6},
//		{51, 51, 1, 14},
//		{61, 61, 1, 14},
//		{51, 51, 2, 14},
//		{61, 61, 2, 14},
//		{51, 51, 3, 14},
//		{52, 60, 3, 0},
//		{61, 61, 3, 14},
//		{51, 51, 4, 14},
//		{51, 51, 5, 14},
//		{51, 51, 6, 14},
//		{51, 51, 7, 13},
//		{52, 61, 7, 1},
//};
//
//void sendDataToEEPROM(unsigned char address, unsigned char bank, unsigned char size)
//{
//    for (unsigned char i = 0; i < size; i++)
//    {
//        EEPROM_WriteBlock(bank, address+i*4, &array[i], 4);
//        __delay_ms(10);
//    }
//    
//    unsigned char buff[4];
//    unsigned char flag = 1;
//    for (unsigned char i = 0; i < size; i++)
//    {
//        EEPROM_ReadBlock(bank, address+i*4, &buff, 4);
//        __delay_ms(10);
//        for (unsigned char j = 0; j < 4; j++)
//        {
//            if (buff[j] != array[i][j])
//            {
//                flag = 0;
//                break;
//            }
//        }
//        if (!flag) break;
//    }
//    if (flag) PORTCbits.RC2 = 1;
//    else PORTCbits.RC3 = 1;
//}
//

static void getVoltage(unsigned char* num)
{
    TRISAbits.TRISA5 = 1;
    ANSELAbits.ANSA5 = 1;
    FVRCON = 0b11000010;
    ADCON0bits.CHS = 0b000101;
    ADCON1 = 0b10100011;
    ADCON0bits.ADON = 1;
    __delay_us(1);
    ADCON0bits.GOnDONE = 1;
    while (ADCON0bits.GOnDONE);
    
    if ((ADRESH << 8)+(ADRESL) <= 661)
    {
        num[0] = 0;
        num[1] = 0;
    }
    else
    {
        unsigned char percent = (unsigned char)(((((ADRESH << 8)+(ADRESL)) - 661) * 100) / 363);
        i = 0;
        while (percent > 0)
        {
            num[i] = (percent % 10);
            percent = (unsigned char)(percent / 10);
            i++;
        }
    }
}

void main(void)
{
    SYSTEM_Initialize();
    
//    TRISC &= ~(1 << 2) & ~(1 << 3) & ~(1 << 4);
////    
//    PORTCbits.RC4 = 1;
    __delay_ms(1000);
//    PORTCbits.RC4 = 0;
    
    
//    
    
//    sendDataToEEPROM(0, 2, 15);
    
//    for (unsigned char i = 0; i < 15; i++)
//    {
//        EEPROM_WriteBlock(5, i, &poses[i], 1);
//        __delay_ms(10);
//    }
//    unsigned char byte = 0;
//    unsigned char flag = 1;
//    for (unsigned char i = 0; i < 15; i++)
//    {
//        EEPROM_ReadBlock(5, i, &byte, 1);
//        if (byte != poses[i])
//        {
//            flag = 0;
//            break;
//        }
//    }
//    if (flag) PORTCbits.RC2 = 1;
//    else PORTCbits.RC3 = 1;
    unsigned char num[2] = {0, 0};
    getVoltage(num);
    drawNumber(num);
    
    
//    __delay_ms(100);
    return;
}
/**
 End of File
*/