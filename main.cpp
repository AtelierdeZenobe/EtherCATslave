/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "EasyCAT.h"

void Application();
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
    
    while(1)
    {
        ThisThread::sleep_for(20ms);
        EASYCAT.MainTask(); 
        Application();
    }
}

void Application()
{
    printf("Byte0: %d\n",EASYCAT.BufferOut.Byte[0]);                                          // Out from Master
    EASYCAT.BufferIn.Byte[0]=0x21;                                      // In to Master
}