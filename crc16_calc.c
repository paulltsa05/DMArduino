
/**
  ******************************************************************************
  * File Name          : crc16_calc.c
  * Description        : 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 KPIT Technologies Ltd.
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "crc16_calc.h"
#include <Arduino.h>
#include <stdlib.h>
#include <stddef.h>
/* Variables -----------------------------------------------------------------*/


/*definition*/
/******************************************************************************************************************************
* @brief  cc_calc_crc16 :This function calculates same crc16 checksum values as of hardware calculated crc16  checksum values
*                         (used on mobile side)
* @return crc16 checksum value :16-bit
******************************************************************************************************************************/
//hardware reflected code of crc16 in software(mobile side crc code)

unsigned short cc_calc_crc16(unsigned char *msg_data, unsigned short data_length)
{
              
unsigned short cc_crc_register;
char cc_msgbit;

cc_crc_register=0xFFFF;           //load all 1's in crc register initially

while(data_length--)
{
	cc_crc_register= cc_crc_register ^ ((unsigned int) *msg_data++ << 8);// (unsigned short) *msg_data++;   //exclusive or msg data with crc_register

	
	for(cc_msgbit=0;cc_msgbit<8;cc_msgbit++)
	{
		      
		   if ( cc_crc_register & 0x8000) 
			 { 
	         cc_crc_register= cc_crc_register <<1;      
			     cc_crc_register= cc_crc_register ^ 0x9001;     // polynomial  -> hex representstion 0x9001
			 }
			 else
			 {
			     cc_crc_register= cc_crc_register <<1;      
			 }
	}
	cc_msgbit=0;
}

return cc_crc_register;  //return crc value
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/







































/*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
#include <stdio.h>

 unsigned char msg_data[]={0x01,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xff,0xa1,0x33,0x6e,0x03};
  

unsigned short crc16(unsigned char *msg_data, unsigned short data_length);

int main(void) {
unsigned short temp;
temp=crc16(msg_data,13);
printf("crcvalue=%X",temp);
	return 0;
}


unsigned short crc16(unsigned char *msg_data, unsigned short data_length)
{
//unsigned short  temp_crc;              
unsigned short crc_register;
char msgbit;

crc_register=0xFFFF;           //load all 1's in crc register initially

while(data_length--)
{
	crc_register= crc_register ^ ((unsigned int) *msg_data++ << 8);// (unsigned short) *msg_data++;   //exclusive or msg data with crc_register

	
	for(msgbit=0;msgbit<8;msgbit++)
	{
		       //shift by 1 to right 
		
			//crc_register= crc_register & 0x7FFF;        //make MSB of crc_register zero(0)
			//temp_crc= crc_register ;                     //storing crc_register value in temp_crc to check if LSB 0 or 1
		//	temp_crc= temp_crc & 0x0001;                 //masking all bits of crc_register expect 1st bit to check if 1 or 0
		      if ( crc_register & 0x8000) 
			{ 
	           crc_register= crc_register <<1;      
			   crc_register= crc_register ^ 0x1021;     // polynomial (x^16 + x^15 +x^2 +1) -> hex representstion 0xA001,->binary representation->1010000000000001
			}
			else
			{
			    crc_register= crc_register <<1;      
			}
			
    }
	msgbit=0;
	
}
//printf("seval=%X",crc_register);
//temp_crc= crc_register & 0x00FF ;
//temp_crc= temp_crc <<8 ;
//crc_register= crc_register & 0xFF00;
//crc_register= crc_register >>8;
//crc_register= crc_register | temp_crc;     //crc16 checksum value
//printf("reverseval=%X",crc_register);
return crc_register;
}
 */




 
















	

/************************ (C) COPYRIGHT KPIT TEchnologies Ltd. *****END OF FILE****/

