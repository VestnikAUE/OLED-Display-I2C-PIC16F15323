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

#include "I2C_functions.h"
#include "../i2c1_master.h"


//i2c1_operations_t wr1ByteCompleteHandler(void *p)
//{
//    I2C1_SetBuffer(p,1);
//    I2C1_SetDataCompleteCallback(NULL,NULL);
//    return I2C1_CONTINUE;
//}

//i2c1_operations_t rd1ByteCompleteHandler(void *p)
//{
//    I2C1_SetBuffer(p,1);
//    I2C1_SetDataCompleteCallback(NULL,NULL);
//    return I2C1_RESTART_READ;
//}

//i2c1_operations_t writeData(void *payload)
//{
//    pageWriteSize_t *pgData = payload;
//    I2C1_SetBuffer(pgData->data,*pgData->dataSize);
//    I2C1_SetDataCompleteCallback(NULL,NULL);
//    return I2C1_CONTINUE;
//}
////////// writes a page
//__bit writePage(uint8_t bank, uint8_t address, uint8_t *dataBlock, uint8_t dataBlockByteCount)
//{
//    pageWriteSize_t pgData = {0};
//    pgData.data = dataBlock;
//    pgData.dataSize = &dataBlockByteCount;
//
//    while(!I2C1_Open(EEPROM_ADDRESS+bank)) PORTCbits.RC4 = 1; // sit here until we get the bus..
//    PORTCbits.RC4 = 0;
//    I2C1_SetDataCompleteCallback(writeData,&pgData);
//    I2C1_SetBuffer(&address,1);
//    I2C1_SetAddressNackCallback(NULL,NULL); //NACK polling?
//    I2C1_MasterWrite();
//    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.
//    
//    return (eeprom_lastError = 0);
//}
//
i2c1_operations_t rdBlockCompleteHandler(void *payload)
{
    pageWriteSize_t *pgData = payload;
    I2C1_SetBuffer(pgData->data,*pgData->dataSize);
    I2C1_SetDataCompleteCallback(NULL,NULL);
    return I2C1_RESTART_READ;
}
/**
 End of File
 */ 
