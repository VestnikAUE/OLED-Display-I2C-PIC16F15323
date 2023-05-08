/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef I2C_FUNCTIONS_H
#define I2C_FUNCTIONS_H

//#include <stdio.h>
//#include <stdint.h>
#include <xc.h>
#include "../i2c1_master.h"

typedef struct
{
    uint8_t *data;
    uint8_t *dataSize;
} pageWriteSize_t;

typedef enum {noError = 0, fail_busy, fail_timeout} eeprom_ErrNo_t;

//typedef uint16_t EEPROM_ADDRESS_t;

//#define PAGESIZE 16
#define EEPROM_ADDRESS 0x50
//#define MIN(a,b) (a<b?a:b)

eeprom_ErrNo_t   eeprom_lastError; // 0 represents no error

//i2c1_operations_t wr1ByteCompleteHandler(void *p);
//i2c1_operations_t rd1ByteCompleteHandler(void *p);
//i2c1_operations_t writeData(void *payload);
//__bit writePage(uint8_t bank, uint8_t address, uint8_t *dataBlock, uint8_t dataBlockByteCount);
i2c1_operations_t rdBlockCompleteHandler(void *payload);

#endif  /*end of I2C_FUNCTIONS_H*/
