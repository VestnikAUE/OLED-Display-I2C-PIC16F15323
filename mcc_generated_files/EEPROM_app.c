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

/**
  Section: Included Files
 */
#ifdef __XC
#include <xc.h>
#endif
//#include <stdbool.h>

#include "EEPROM_app.h"
#include "i2c1_master.h"

/**
  Section: Driver APIs
 */ 
//
//void EEPROM_WriteBlock(uint8_t bank, uint8_t address, void *dataBlock, uint8_t dataBlockByteCount)
//{   
//    int byte2write = PAGESIZE;
//    
//    do
//    {
//        byte2write = MIN(byte2write,dataBlockByteCount);
//        writePage(bank, address,dataBlock,byte2write);
//        if (eeprom_lastError)
//            break;
//        address += byte2write;
//        dataBlock += byte2write;
//        dataBlockByteCount -= byte2write;
//        byte2write = PAGESIZE;
//    } while(dataBlockByteCount);
//}

void EEPROM_ReadBlock(uint8_t bank, uint8_t address, void *dataBlock, uint8_t dataBlockByteCount)
{
    pageWriteSize_t pgData = {0};
    pgData.data = dataBlock;
    pgData.dataSize = &dataBlockByteCount;
    
    while(!I2C1_Open(EEPROM_ADDRESS+bank));
    I2C1_SetDataCompleteCallback(rdBlockCompleteHandler,&pgData);
    I2C1_SetBuffer(&address,1);
    I2C1_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C1_MasterWrite();
    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.
}

/**
 End of File
 */ 
