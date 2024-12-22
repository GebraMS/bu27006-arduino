/*
 * ________________________________________________________________________________________________________
 * Copyright (c) 2020 GebraBit Inc. All rights reserved.
 *
 * This software, related documentation and any modifications thereto (collectively �Software�) is subject
 * to GebraBit and its licensors' intellectual property rights under U.S. and international copyright
 * and other intellectual property rights laws. 
 *
 * GebraBit and its licensors retain all intellectual property and proprietary rights in and to the Software
 * and any use, reproduction, disclosure or distribution of the Software without an express license agreement
 * from GebraBit is strictly prohibited.
 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT IN  
 * NO EVENT SHALL GebraBit BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, 
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 * @Author       	: Sepehr Azimi
 * ________________________________________________________________________________________________________
 */
#ifndef	__BU27006MUCZ_H__
#define	__BU27006MUCZ_H__
#include "arduino.h"
#include "Wire.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

/************************************************
 *              USER REGISTER MAP               *
 ***********************************************/ 
#define BU27006MUCZ_SYSTEM_CONTROL  		0x40
#define BU27006MUCZ_MODE_CONTROL1  			0x41
#define BU27006MUCZ_MODE_CONTROL2 			0x42
#define BU27006MUCZ_MODE_CONTROL3 			0x43
#define BU27006MUCZ_RED_DATA 					  0x50  //2 byte
#define BU27006MUCZ_GREEN_DATA 				  0x52  //2 byte
#define BU27006MUCZ_BLUE_DATA 				  0x54  //2 byte
#define BU27006MUCZ_IR_DATA 				    0x56  //2 byte
#define BU27006MUCZ_FLICKER_DATA 				0x58  //2 byte
#define BU27006MUCZ_FLICKER_COUNTER 		0x5A
#define BU27006MUCZ_FIFO_LEVEL 					0x5B
#define BU27006MUCZ_FIFO_DATA 					0x5C  //2 byte
#define BU27006MUCZ_MANUFACTURER_ID 		0x92
#define BU27006MUCZ_I2C		              &hi2c1	
#define BU27006MUCZ_ADDRESS 							0x38
/*----------------------------------------------*
 *           USER REGISTER MAP End              *
 *----------------------------------------------*/ 
 /************************************************
 *         MSB Bit Start Location Begin         *
 ***********************************************/ 
#define START_MSB_BIT_AT_0                    0
#define START_MSB_BIT_AT_1                    1
#define START_MSB_BIT_AT_2                    2
#define START_MSB_BIT_AT_3                    3
#define START_MSB_BIT_AT_4                    4
#define START_MSB_BIT_AT_5                    5
#define START_MSB_BIT_AT_6                    6
#define START_MSB_BIT_AT_7                    7
/*----------------------------------------------*
 *        MSB Bit Start Location End            *
 *----------------------------------------------*/ 
/************************************************
 *          Bit Field Length Begin              *
 ***********************************************/ 
#define BIT_LENGTH_1                          1
#define BIT_LENGTH_2                          2
#define BIT_LENGTH_3                          3
#define BIT_LENGTH_4                          4
#define BIT_LENGTH_5                          5
#define BIT_LENGTH_6                          6
#define BIT_LENGTH_7                          7
#define BIT_LENGTH_8                          8
/*----------------------------------------------*
 *          Bit Field Length End                *
 *----------------------------------------------*/
#define REGISTER_DATA_BUFFER_SIZE             10
#define FIFO_DATA_BUFFER_SIZE                 100
#define COLOR_LUX_RESOLUTION                  0.015f
/**************************************************
 *     Values For Disable And Enable Functions    *
 **************************************************/ 
typedef enum Ability
{  
	Disable = 0     ,                      
	Enable     
}BU27006MUCZ_Ability;    
/*************************************************
 *           Values For Reset Process             *
 **************************************************/ 
typedef enum 
{  
	FAILED = 0     ,                      
	DONE     
}BU27006MUCZ_Reset_Status;
/*************************************************
 *         Values For  Interrupt Channel         *
 **************************************************/ 
typedef enum Interrupt_Channel 
{  
	CLEAR_CHANNEL = 0     ,                      
	ALS_CHANNEL     
}BU27006MUCZ_Interrupt_Channel;
/*************************************************
 *    				 Values For RGB Gain  	   	       *
 **************************************************/ 
typedef enum RGB_Gain 
{
  RGB_GAIN_1X   = 0,
  RGB_GAIN_4X   = 1,
  RGB_GAIN_32X  = 2,
  RGB_GAIN_128X = 3,
} BU27006MUCZ_RGB_Gain;
/*************************************************
 *    				 Values For FLC Gain  	   	       *
 **************************************************/ 
typedef enum FLC_Gain 
{
  FLC_GAIN_1X   = 0,
  FLC_GAIN_2X   = 1,
  FLC_GAIN_4X   = 2,
  FLC_GAIN_8X   = 3,
	FLC_GAIN_16X  = 4,
  FLC_GAIN_32X  = 5
} BU27006MUCZ_FLC_Gain;
/*************************************************
 *      	Values For RGB Measurement Mode  	   	 *
 **************************************************/ 
typedef enum RGB_Measurement_Mode
{
	_55_mS_MODE  = 1,
  _100_mS_MODE = 2
} BU27006MUCZ_RGB_Measurement_Mode;
/*************************************************
 *      	Values For FLC Measurement Mode  	   	 *
 **************************************************/ 
typedef enum FLC_Measurement_Mode
{
  _1_KHZ_MODE,
  _2_KHZ_MODE
} BU27006MUCZ_FLC_Measurement_Mode;
/*************************************************
 *      	Values For FLC Interrupt Mode  	   	   *
 **************************************************/
typedef enum Interrupt_Mode
{
	INTERRUPT_DISABLE,
  RGB_IR_COMPELETION,
  FLICKER_COMPELETION,
  FIFO_64_DATA_READY
} BU27006MUCZ_Interrupt_Mode;
/*************************************************
 *           Values For Data Status              *
 **************************************************/ 
typedef enum Data_Status 
{  
	NOT_UPDATED = 0     ,                      
	UPDATED     
}BU27006MUCZ_Data_Status;
/*************************************************
 *           Values For Interrupt Status         *
 **************************************************/ 
typedef enum Interrupt_Status 
{  
	INTERRUPT_NOT_FULFILLED = 0     ,                      
	INTERRUPT_FULFILLED     
}BU27006MUCZ_Interrupt_Status;

 /*************************************************
 *  Defining BU27006MUCZ Register & Data As Struct   *
 **************************************************/
typedef	struct BU27006MUCZ
{
	  uint8_t                       		 Register_Cache;
	  uint8_t														 PART_ID;
	  uint8_t														 MANUFACTURER_ID;
	  BU27006MUCZ_Reset_Status					 RESET;
	  BU27006MUCZ_Ability                RGB_IR;
	  BU27006MUCZ_Ability                FLC;
	  BU27006MUCZ_RGB_Gain               RGB_GAIN;
	  BU27006MUCZ_RGB_Measurement_Mode   RGB_MEASUREMENT_MODE;
	  BU27006MUCZ_FLC_Gain               FLC_GAIN;
	  BU27006MUCZ_FLC_Measurement_Mode   FLC_MEASUREMENT_MODE;
	  float															 ALS_RESOLUTION_TIME;
	  BU27006MUCZ_Data_Status            RGB_DATA;
	  BU27006MUCZ_Data_Status            FLC_DATA;	  
	  BU27006MUCZ_Interrupt_Mode         INTERRUPT_MODE;
    BU27006MUCZ_Interrupt_Channel      INTERRUPT_CHANNEL;
	  uint8_t         									 FLICKER_COUNTER;
	  uint8_t                            FIFO_LEVEL;
	  BU27006MUCZ_Interrupt_Status			 INTERRRUPT_STATUS;
	  uint32_t                        	 INTERRUPT_UPPER_THRESHOLD;
	  uint32_t                           INTERRUPT_LOWER_THRESHOLD;
		uint8_t 												   REGISTER_DATA[REGISTER_DATA_BUFFER_SIZE];
		uint16_t               					   RED_DATA;
		uint16_t               					   GREEN_DATA;
		uint16_t               					   BLUE_DATA;
		uint16_t               					   IR_DATA;
		uint16_t               					   FLICKER_DATA;
		uint16_t 												   FIFO_DATA[FIFO_DATA_BUFFER_SIZE];
    float 														 RED_LUX;
		float 														 GREEN_LUX;
		float 														 BLUE_LUX;
}GebraBit_BU27006MUCZ;
/*
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/********************************************************
 *  Declare Read&Write MS5611 Register Values Functions *
 ********************************************************/
extern void GB_BU27006MUCZ_Read_Reg_Data(uint8_t regAddr,  uint8_t *data)	;
extern void GB_BU27006MUCZ_Burst_Read(uint8_t regAddr,  uint8_t *data, uint16_t byteQuantity);
extern void GB_BU27006MUCZ_Read_Reg_Bits (uint8_t regAddr, uint8_t start_bit, uint8_t len, uint8_t* data);	
extern void GB_BU27006MUCZ_Write_Command( uint8_t cmd);
extern void GB_BU27006MUCZ_Write_Reg_Data(uint8_t regAddr,  uint8_t data)	;
extern void GB_BU27006MUCZ_Burst_Write(uint8_t regAddr,  uint8_t *data, uint16_t byteQuantity)								;
extern void GB_BU27006MUCZ_Write_Reg_Bits(uint8_t regAddr, uint8_t start_bit, uint8_t len, uint8_t data);
/********************************************************
 *       Declare MS5611 Configuration Functions         *
 ********************************************************/
extern void GB_BU27006MUCZ_Soft_Reset ( GebraBit_BU27006MUCZ * BU27006MUCZ )  ;
extern void GB_BU27006MUCZ_RGB_Gain ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_RGB_Gain gain ) ;
extern void GB_BU27006MUCZ_RGB_Measurement_Mode ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_RGB_Measurement_Mode mode )   ;
extern void GB_BU27006MUCZ_FLC_Measurement_Mode ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_FLC_Measurement_Mode mode )   ;
extern void GB_BU27006MUCZ_FLC_Gain ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_FLC_Gain gain ) ;
extern void GB_BU27006MUCZ_RGB_IR ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_Ability rgb )   ;
extern void GB_BU27006MUCZ_FLC ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_Ability flc );
extern void GB_BU27006MUCZ_Interrupt(GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_Interrupt_Mode mode)  ;
extern void GB_BU27006MUCZ_Check_Data_Updated ( GebraBit_BU27006MUCZ * BU27006MUCZ )  ;
extern void GB_BU27006MUCZ_Part_ID ( GebraBit_BU27006MUCZ * BU27006MUCZ  )  ;
extern void GB_BU27006MUCZ_Manufacture_ID ( GebraBit_BU27006MUCZ * BU27006MUCZ  )  ;
extern void GB_BU27006MUCZ_Flicker_Counter ( GebraBit_BU27006MUCZ * BU27006MUCZ ) ;
extern void GB_BU27006MUCZ_FIFO_Level ( GebraBit_BU27006MUCZ * BU27006MUCZ ) ;
extern void GB_BU27006MUCZ_Read_FIFO_Flicker_Data ( GebraBit_BU27006MUCZ * BU27006MUCZ );
extern void GB_BU27006MUCZ_initialize( GebraBit_BU27006MUCZ * BU27006MUCZ )  ;
extern void GB_BU27006MUCZ_Configuration(GebraBit_BU27006MUCZ * BU27006MUCZ)  ;
extern void GB_BU27006MUCZ_Read_RGB_IR_FLICKER(GebraBit_BU27006MUCZ * BU27006MUCZ);
extern void GB_BU27006MUCZ_Color_Luminosity(GebraBit_BU27006MUCZ * BU27006MUCZ);
extern void GB_BU27006MUCZ_Get_Data(GebraBit_BU27006MUCZ * BU27006MUCZ);
#endif
