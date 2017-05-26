/**
  ******************************************************************************
  * File Name          : crc16_calc.h
  * Description        : This file contains all the function prototypes for
  *                      the crc16_calc.c file
  ******************************************************************************
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __crc16_calc_H
#define __crc16_calc_H
#ifdef __cplusplus
extern "C" {
#endif

/**********************variables********************************************************/



	 
/**************function prototypes******************************************************/



unsigned short cc_calc_crc16(unsigned char *cc_msg_data, unsigned short cc_data_length);




#ifdef __cplusplus
}
#endif

#endif /* __crc16_calc_H */

/**
  * @}
  */
