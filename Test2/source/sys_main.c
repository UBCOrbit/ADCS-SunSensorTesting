/** @file sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */

#include "sci.h"

#include "adc.h"

#include "stdlib.h"

unsigned char command[8];

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#include "gio.h"

#include "het.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    int waittime = 6000000;

    int i;

    gioInit();

    hetInit();



    adcData_t adc_data; //ADC Data Structure
    //adcData_t adc_data[2];//array of adc data to account to multiple pins
    adcData_t *adc_data_ptr = &adc_data; //ADC Data Pointer

    unsigned int NumberOfChars, value; //Declare variables



     sciInit(); //Initializes the SCI (UART) module

     adcInit(); //Initializes the ADC module




     while(1) {



        adcStartConversion(adcREG1, adcGROUP1); //Start ADC conversion

         while(!adcIsConversionComplete(adcREG1, adcGROUP1)); //Wait for ADC conversion

         adcGetData(adcREG1, 1U, adc_data_ptr); //Store conversion into ADC pointer
         //adcGetData(adcREG1, adcGROUP1,&adc_data[0]);

         /*id[0] = adc_data[0].id;       //First pin id
         value[0] = adc_data[0].value; //First pin value

         id[1] = adc_data[0].id;       //Second pin id
         value[1] = adc_data[0].value; //*/


         value = (unsigned int)adc_data_ptr->value;

         NumberOfChars = ltoa(value,(char *)command);

         sciSend(scilinREG, 2, (unsigned char *)"0x"); //Sends '0x' hex designation chars

         sciSend(scilinREG, NumberOfChars, command); //Sends the ambient light sensor data

          sciSend(scilinREG, 2, (unsigned char *)"\r\n"); //Sends new line character

          for(i=0;i<waittime;i++){
              //waiter
          }

    }



/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void adcNotification(adcBASE_t *adc, unsigned group)

{

    return;

}



void sciNotification(sciBASE_t *sci, unsigned flags)

{

    return;

}



void esmGroup1Notification(int bit)

{

  return;

}



void esmGroup2Notification(int bit)

{

  return;

}
/* USER CODE END */
