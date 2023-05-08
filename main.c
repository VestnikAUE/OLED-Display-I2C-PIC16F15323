/*
    PIC16F15323
    Program Memory: 2048 bytes (170 free)
    Dynamic Memory: 256 bytes (57 free)

    SSD1306 128x32 (I2C)
    Horizontal Addressing Mode

    24AA16 EEPROM
    Data: 2048 bytes (1250 free)
*/

#include "CONFIG.h"

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/EEPROM_app.h"

#define DISPLAY_ADDR 0x3C // адрес дисплея

// Цифры
static unsigned char adrs[12][3] = // {адрес в EEPROM, номер сегмента памяти, размер}
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

static unsigned char i = 0;
static unsigned char buff[2] = {0xC0, 0x00};
static unsigned char list[26];

// Инициализация дисплея
static void initialize_oled()
{
    list[0] = 0x00;
    for (unsigned char i = 1; i < 26; i++)
        EEPROM_ReadBlock(4, i, &list[i], 1);
    I2C1_WriteNBytes(DISPLAY_ADDR, list, 26);
    unsigned char ret[7] = {0x00, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x7};
    I2C1_WriteNBytes(DISPLAY_ADDR, ret, 7); // вернуть указатель в памяти дисплея в верхний правый угол
}

// Очищение памяти дисплея
static void clearGDDRAM()
{
    for (unsigned short i = 0; i < 128*8; i++)
        I2C1_WriteNBytes(DISPLAY_ADDR, buff, 2);
}

// Изображение двузначного числа на дисплее
static void drawNumber(unsigned char* num)
{
    i = 0;
    unsigned char array[2][3][4];
    unsigned char iter1 = 0;
    unsigned char iter2 = 0;    
    initialize_oled();
    clearGDDRAM();
    unsigned char k = 0;
    unsigned char l = 0;
    unsigned char j = 0;
    unsigned char count[2];
    for (unsigned char n = 0; n < 8; n++)
    {
        for (i = 0; i < 3-(adrs[*num][2]-iter1<3)*(3-adrs[*num][2]+iter1); i++)
            EEPROM_ReadBlock(adrs[*num][1], adrs[*num][0]+(i+iter1)*4, &array[0][i], 4);
        for (i = 0; i < 3-(adrs[*(num+1)][2]-iter2<3)*(3-adrs[*(num+1)][2]+iter2); i++)
        {            
            EEPROM_ReadBlock(adrs[*(num+1)][1], adrs[*(num+1)][0]+(i+iter2)*4, &array[1][i], 4);
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

// Снятие процента заряда с батареи
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
    SYSTEM_Initialize(); // инициализация подключения I2C
    
    __delay_ms(1000);

    unsigned char num[2] = {0, 0};
    getVoltage(num);
    drawNumber(num);
    
    return;
}
