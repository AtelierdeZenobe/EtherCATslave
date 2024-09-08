/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "EasyCAT.h"
#include <cstdint>
#include <string>

using namespace std;
void Application(int count);
//-----------------------------------------------------------

EasyCAT EASYCAT;                    // Without any parameter pin 9 will be used 
                                  
int main()
{
    if(EASYCAT.Init()) 
    {
        printf("Initialized \n");
    }
    else
    {
        printf("Initialization failed \n");
    }
    
    // From EasyCAT.h
    /*
    #define ESM_INIT                0x01                  // init
    #define ESM_PREOP               0x02                  // pre-operational
    #define ESM_BOOT                0x03                  // bootstrap
    #define ESM_SAFEOP              0x04                  // safe-operational
    #define ESM_OP                  0x08                  // operational
    */
    unsigned char status;
    uint8_t uiStatus;
    int sendCount = 0; //Will vary between 100 and 110
    while(1)
    {
        ThisThread::sleep_for(20ms);

        // Check state
        status = EASYCAT.MainTask(); // Must be called cyclically
        uiStatus = static_cast<uint8_t>(status & 0x7F);
        if(uiStatus < 4)
            printf("Status: %u\n", uiStatus);

        Application((sendCount%10) + 100);
        sendCount++;

        //ThisThread::sleep_for(1000);
    }
}

void Application(int count)
{
    if(count % 100 == 0)
    {
        printf("wanted distance MSB: %02x\n",EASYCAT.BufferOut.Byte[0]);
        printf("wanted distance: LSB: %02x\n",EASYCAT.BufferOut.Byte[1]);
        printf("wanted angle MSB: %02x\n",EASYCAT.BufferOut.Byte[2]);
        printf("wanted angle LSB: %02x\n",EASYCAT.BufferOut.Byte[3]);
    }
    //TODO: EasyCAT.h offers a Custom Mode allowing so specify a data type

    // state is one byte and other is 2 bytes
    EASYCAT.BufferIn.Byte[0]=0x01;
    EASYCAT.BufferIn.Byte[1]=0x02;
    EASYCAT.BufferIn.Byte[2]=0x03;  
}