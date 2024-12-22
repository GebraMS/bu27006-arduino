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
#include "GebraBit_BU27006MUCZ.h"

/*========================================================================================================================================= 
 * @brief     Read  data from  spacial register address.
 * @param     regAddr Register Address of BU27006MUCZ that reading data from this address
 * @param     data    Pointer to Variable that data is saved .
 * @return    None
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Read_Reg_Data(uint8_t regAddr,  uint8_t *data)																			/*		Read Burst Data From Register			*/
{
	Wire.beginTransmission(BU27006MUCZ_ADDRESS);
    Wire.write(regAddr); 
    Wire.endTransmission(false); 
    Wire.requestFrom((uint8_t)BU27006MUCZ_ADDRESS, (uint8_t)1);
	delay(15);
    if (Wire.available()) {
        *data = Wire.read(); 
    }
}
/*========================================================================================================================================= 
 * @brief     Read multiple data from first spacial register address.
 * @param     regAddr First Register Address of BU27006MUCZ that reading multiple data start from this address
 * @param     data    Pointer to Variable that multiple data is saved .
 * @param     byteQuantity Quantity of data that we want to read .
 * @return    None
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Burst_Read(uint8_t regAddr,  uint8_t *data, uint16_t byteQuantity)																			/*		Read Burst Data From Register			*/
{
	Wire.beginTransmission(BU27006MUCZ_ADDRESS);
    Wire.write(regAddr); 
    Wire.endTransmission(false); 
    Wire.requestFrom((uint8_t)BU27006MUCZ_ADDRESS, (uint8_t)byteQuantity); 
	delay(15);
    for (uint16_t i = 0; i < byteQuantity; i++) {
        if (Wire.available()) {
            data[i] = Wire.read();
        }
    }
}
/*========================================================================================================================================= 
 * @brief     Read data from spacial bits of a register.
 * @param     regAddr     Register Address of BU27006MUCZ .
 * @param     start_bit   Start Bit location .(0 to 7)
 * @param     len         Quantity of Bits want to read(1 to 8) 
 * @param     data        Pointer to Variable that register Bits value is saved .
 * @return    status      Return status
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Read_Reg_Bits (uint8_t regAddr, uint8_t start_bit, uint8_t len, uint8_t* data)
{
	uint8_t tempData = 0;
	GB_BU27006MUCZ_Read_Reg_Data( regAddr, &tempData);
	uint8_t mask = ((1 << len) - 1) << (start_bit - len + 1); //formula for making a broom of 1&0 for gathering desired bits
	tempData &= mask; // zero all non-important bits in data
	tempData >>= (start_bit - len + 1); //shift data to zero position
	*data = tempData;
}
/*=========================================================================================================================================
 * @param     cmd    Command that will be writen 
 * @return    status    Return status
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Write_Command( uint8_t cmd)
{
	uint8_t TBuff[1];
	TBuff[0]=cmd;
	Wire.beginTransmission(BU27006MUCZ_ADDRESS);
	Wire.write(cmd); 
    Wire.endTransmission(); 
}
/*========================================================================================================================================= 
 * @brief     Write  data to  spacial register address.
 * @param     regAddr First Register Address of BU27006MUCZ that reading multiple data start from this address
 * @param     data    Variable that to be written .
 * @return    None
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Write_Reg_Data(uint8_t regAddr,  uint8_t data)																			/*		Read Burst Data From Register			*/
{
	Wire.beginTransmission(BU27006MUCZ_ADDRESS);
    Wire.write(regAddr); 
    Wire.write(data); 
    Wire.endTransmission();
}
/*========================================================================================================================================= 
 * @brief     Write multiple data from first spacial register address.
 * @param     regAddr First Register Address of BU27006MUCZ that  multiple data to be written start from this address
 * @param     data    Pointer to multiple data Variable that to be written.
 * @param     byteQuantity Quantity of data that we want to Write .
 * @return    None
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Burst_Write(uint8_t regAddr,  uint8_t *data, uint16_t byteQuantity)																			/*		Read Burst Data From Register			*/
{
	Wire.beginTransmission(BU27006MUCZ_ADDRESS);
    Wire.write(regAddr);
	delay(15);
	for (uint16_t i = 0; i < byteQuantity; i++){
		Wire.write(data[i]);
	}
    Wire.endTransmission();
}
/*=========================================================================================================================================
 * @brief     Write data to spacial bits of a register.
 * @param     regAddr     Register Address of BU27006MUCZ .
 * @param     start_bit   Start Bit location .(0 to 7)
 * @param     len         Quantity of Bits want to write(1 to 8) 
 * @param     data        Value that will be writen to register bits .
 * @return    status      Return status
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Write_Reg_Bits(uint8_t regAddr, uint8_t start_bit, uint8_t len, uint8_t data)
{
	uint8_t tempData = 0;
	GB_BU27006MUCZ_Read_Reg_Data( regAddr, &tempData) ;	
	uint8_t mask = ((1 << len) - 1) << (start_bit - len + 1);
	data <<= (start_bit - len + 1); // shift data into correct position
	data &= mask; // zero all non-important bits in data
	tempData &= ~(mask); // zero all important bits in existing byte
	tempData |= data; // combine data with existing byte
	GB_BU27006MUCZ_Write_Reg_Data(regAddr,  tempData);
}
/*=========================================================================================================================================
 * @brief     Reset BU27006MUCZ
 * @param     BU27006MUCZ   BU27006MUCZ Struct RESET Variable.
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Soft_Reset ( GebraBit_BU27006MUCZ * BU27006MUCZ )  
{
	GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_SYSTEM_CONTROL, START_MSB_BIT_AT_7, BIT_LENGTH_1, 1);
	delay(100);
	BU27006MUCZ->RESET = DONE ;
}

/*=========================================================================================================================================
 * @brief     Set RGB Gain
 * @param     BU27006MUCZ   BU27006MUCZ Struct RGB_GAIN variable
 * @param     gain        Value is from BU27006MUCZ_RGB_Gain Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_RGB_Gain ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_RGB_Gain gain ) 
{
 GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL1, START_MSB_BIT_AT_5, BIT_LENGTH_2, gain);
 BU27006MUCZ->RGB_GAIN = gain ;
}
/*=========================================================================================================================================
 * @brief     Set RGB Measurement Mode
 * @param     BU27006MUCZ   BU27006MUCZ Struct RGB_MEASUREMENT_MODE variable
 * @param     mode        Value is from BU27006MUCZ_RGB_Measurement_Mode Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_RGB_Measurement_Mode ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_RGB_Measurement_Mode mode ) 
{
 GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL1, START_MSB_BIT_AT_1, BIT_LENGTH_2, mode);
 BU27006MUCZ->RGB_MEASUREMENT_MODE = mode ;
}
/*=========================================================================================================================================
 * @brief     Set FLC Gain
 * @param     BU27006MUCZ   BU27006MUCZ Struct FLC_GAIN variable
 * @param     gain        Value is from BU27006MUCZ_FLC_Gain Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_FLC_Gain ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_FLC_Gain gain ) 
{
 GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL2, START_MSB_BIT_AT_5, BIT_LENGTH_3, gain);
 BU27006MUCZ->FLC_GAIN = gain ;
}
/*=========================================================================================================================================
 * @brief     Set FLC Measurement Mode
 * @param     BU27006MUCZ   BU27006MUCZ Struct FLC_MEASUREMENT_MODE variable
 * @param     mode        Value is from BU27006MUCZ_FLC_Measurement_Mode Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_FLC_Measurement_Mode ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_FLC_Measurement_Mode mode ) 
{
 GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL2, START_MSB_BIT_AT_0, BIT_LENGTH_1, mode);
 BU27006MUCZ->FLC_MEASUREMENT_MODE = mode ;
}
/*=========================================================================================================================================
 * @brief     Enable Or Disable RGB & IR
 * @param     BU27006MUCZ   BU27006MUCZ Struct RGB_IR variable
 * @param     rgb        Value is from BU27006MUCZ_Ability Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_RGB_IR ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_Ability rgb ) 
{
 GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL3, START_MSB_BIT_AT_1, BIT_LENGTH_1, rgb);
 BU27006MUCZ->RGB_IR = rgb ;
}
/*=========================================================================================================================================
 * @brief     Enable Or Disable FLC
 * @param     BU27006MUCZ   BU27006MUCZ Struct FLC variable
 * @param     flc        Value is from BU27006MUCZ_Ability Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_FLC ( GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_Ability flc ) 
{
 GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL3, START_MSB_BIT_AT_0, BIT_LENGTH_1, flc);
 BU27006MUCZ->FLC = flc ;
}
/*=========================================================================================================================================
 * @brief     Set Interrupt Mode
 * @param     BU27006MUCZ   BU27006MUCZ Struct INTERRUPT_MODE variable
 * @param     mode        Value is from BU27006MUCZ_Interrupt_Mode Enume
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Interrupt(GebraBit_BU27006MUCZ * BU27006MUCZ , BU27006MUCZ_Interrupt_Mode mode)
{   
  GB_BU27006MUCZ_Write_Reg_Bits(BU27006MUCZ_MODE_CONTROL3, START_MSB_BIT_AT_3, BIT_LENGTH_2, mode);
  BU27006MUCZ->INTERRUPT_MODE = mode ;
}
/*=========================================================================================================================================
 * @brief     Check if Data is Updated
 * @param     BU27006MUCZ   BU27006MUCZ Struct RGB_DATA variable & FLC_DATA variable
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Check_Data_Updated ( GebraBit_BU27006MUCZ * BU27006MUCZ ) 
{
 uint8_t status;
 GB_BU27006MUCZ_Read_Reg_Data(BU27006MUCZ_MODE_CONTROL3, &status);
 BU27006MUCZ->RGB_DATA = (status & 0x80)>>7  ;
 BU27006MUCZ->FLC_DATA = (status & 0x40)>>6  ; 
}
/*=========================================================================================================================================
 * @brief     Read BU27006MUCZ Part ID
 * @param     BU27006MUCZ   BU27006MUCZ Struct PART_ID variable
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Part_ID ( GebraBit_BU27006MUCZ * BU27006MUCZ  ) 
{
 GB_BU27006MUCZ_Read_Reg_Bits(BU27006MUCZ_SYSTEM_CONTROL, START_MSB_BIT_AT_5, BIT_LENGTH_6, &BU27006MUCZ->PART_ID);
}
/*=========================================================================================================================================
 * @brief     Read BU27006MUCZ Manufacture ID
 * @param     BU27006MUCZ   BU27006MUCZ Struct MANUFACTURER_ID variable
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Manufacture_ID ( GebraBit_BU27006MUCZ * BU27006MUCZ  ) 
{
 GB_BU27006MUCZ_Read_Reg_Data(BU27006MUCZ_MANUFACTURER_ID, &BU27006MUCZ->MANUFACTURER_ID); 
}


/*=========================================================================================================================================
 * @brief     Read BU27006MUCZ Flicker Counter Value
 * @param     BU27006MUCZ   BU27006MUCZ Struct FLICKER_COUNTER variable
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Flicker_Counter ( GebraBit_BU27006MUCZ * BU27006MUCZ ) 
{
 GB_BU27006MUCZ_Read_Reg_Data(BU27006MUCZ_FLICKER_COUNTER, &BU27006MUCZ->FLICKER_COUNTER );
}
/*=========================================================================================================================================
 * @brief     Read BU27006MUCZ FIFO Level Value
 * @param     BU27006MUCZ   BU27006MUCZ Struct FIFO_LEVEL variable
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_FIFO_Level ( GebraBit_BU27006MUCZ * BU27006MUCZ ) 
{
 GB_BU27006MUCZ_Read_Reg_Data(BU27006MUCZ_FIFO_LEVEL, &BU27006MUCZ->FIFO_LEVEL); 
}
/*=========================================================================================================================================
 * @brief     Read BU27006MUCZ Flicker Data from FIFO
 * @param     BU27006MUCZ   BU27006MUCZ Struct FIFO_DATA variable
 * @return    Nothing
 ========================================================================================================================================*/
void GB_BU27006MUCZ_Read_FIFO_Flicker_Data ( GebraBit_BU27006MUCZ * BU27006MUCZ ) 
{
	uint8_t i = 0;
  uint8_t fifo[2]={0,0};
	GB_BU27006MUCZ_FIFO_Level(BU27006MUCZ );
	for(i=0 ; i<BU27006MUCZ->FIFO_LEVEL ; i++)
	 {
    GB_BU27006MUCZ_Burst_Read( BU27006MUCZ_FIFO_DATA , fifo , 2);
		BU27006MUCZ->FIFO_DATA[i] = ((uint16_t)(fifo[1]<<8)) | ((uint16_t)fifo[0]);
	 }
	GB_BU27006MUCZ_FLC_Measurement_Mode (BU27006MUCZ ,BU27006MUCZ->FLC_MEASUREMENT_MODE  );//FIFO_LEVEL register and FIFO_DATA register are cleared by writing MODE_CONTROL1 to MODE_CONTROL3 registers
	delay(330);
}
/*
M403Z 
*/
/*=========================================================================================================================================
 * @brief     initialize BU27006MUCZ
 * @param     BU27006MUCZ     BU27006MUCZ Struct 
 * @return    Nothing
 ========================================================================================================================================*/ 
void GB_BU27006MUCZ_initialize( GebraBit_BU27006MUCZ * BU27006MUCZ )
{
  GB_BU27006MUCZ_Soft_Reset   ( BU27006MUCZ ) ;
  GB_BU27006MUCZ_Part_ID ( BU27006MUCZ ) ;
	GB_BU27006MUCZ_Manufacture_ID( BU27006MUCZ ) ;
	GB_BU27006MUCZ_Interrupt( BU27006MUCZ , INTERRUPT_DISABLE ) ;
	GB_BU27006MUCZ_FLC (  BU27006MUCZ , Enable   );
	GB_BU27006MUCZ_RGB_IR( BU27006MUCZ , Enable ) ;
}
/*=========================================================================================================================================
 * @brief     Configure BU27006MUCZ
 * @param     BU27006MUCZ  Configure BU27006MUCZ 
 * @return    Nothing
 ========================================================================================================================================*/ 
void GB_BU27006MUCZ_Configuration(GebraBit_BU27006MUCZ * BU27006MUCZ)
{
	GB_BU27006MUCZ_RGB_Gain( BU27006MUCZ , RGB_GAIN_4X ) ;
	GB_BU27006MUCZ_FLC_Gain( BU27006MUCZ , FLC_GAIN_4X ) ;
	GB_BU27006MUCZ_RGB_Measurement_Mode( BU27006MUCZ , _100_mS_MODE ) ;
	GB_BU27006MUCZ_FLC_Measurement_Mode ( BU27006MUCZ ,  _1_KHZ_MODE );
}
/*=========================================================================================================================================
 * @brief     Get Raw Data Of RGB & IR & FLICKER
 * @param     BU27006MUCZ  store Raw Data Of RGB & IR & FLICKER in GebraBit_BU27006MUCZ Struct RED_DATA & GREEN_DATA & BLUE_DATA & IR_DATA & FLICKER_DATA
 * @return    Nothing
 ========================================================================================================================================*/ 
void GB_BU27006MUCZ_Read_RGB_IR_FLICKER(GebraBit_BU27006MUCZ * BU27006MUCZ)
{
	GB_BU27006MUCZ_Flicker_Counter( BU27006MUCZ );
	GB_BU27006MUCZ_Check_Data_Updated( BU27006MUCZ );
	if ( (BU27006MUCZ->RGB_DATA== UPDATED) && (BU27006MUCZ->FLC_DATA== UPDATED) ) 
	{    
   GB_BU27006MUCZ_Burst_Read( BU27006MUCZ_RED_DATA , BU27006MUCZ->REGISTER_DATA , REGISTER_DATA_BUFFER_SIZE);
	 BU27006MUCZ->RED_DATA     = ((uint16_t)BU27006MUCZ->REGISTER_DATA[1]<<8)|((uint16_t)BU27006MUCZ->REGISTER_DATA[0]);
   BU27006MUCZ->GREEN_DATA   = ((uint16_t)BU27006MUCZ->REGISTER_DATA[3]<<8)|((uint16_t)BU27006MUCZ->REGISTER_DATA[2]);
	 BU27006MUCZ->BLUE_DATA    = ((uint16_t)BU27006MUCZ->REGISTER_DATA[5]<<8)|((uint16_t)BU27006MUCZ->REGISTER_DATA[4]);
   BU27006MUCZ->IR_DATA      = ((uint16_t)BU27006MUCZ->REGISTER_DATA[7]<<8)|((uint16_t)BU27006MUCZ->REGISTER_DATA[6]);
   BU27006MUCZ->FLICKER_DATA = ((uint16_t)BU27006MUCZ->REGISTER_DATA[9]<<8)|((uint16_t)BU27006MUCZ->REGISTER_DATA[8]);
	}
}  
/*=========================================================================================================================================
 * @brief     Get Color Luminosity
 * @param     BU27006MUCZ  store Color Luminosity in GebraBit_BU27006MUCZ Struct RED_LUX & GREEN_LUX & BLUE_LUX
 * @return    Nothing
 ========================================================================================================================================*/ 
void GB_BU27006MUCZ_Color_Luminosity(GebraBit_BU27006MUCZ * BU27006MUCZ)
{ 
	 BU27006MUCZ->RED_LUX   = (float)BU27006MUCZ->RED_DATA     * COLOR_LUX_RESOLUTION ; 
   BU27006MUCZ->GREEN_LUX = (float)BU27006MUCZ->GREEN_DATA   * COLOR_LUX_RESOLUTION ; 
	 BU27006MUCZ->BLUE_LUX  = (float)BU27006MUCZ->BLUE_DATA    * COLOR_LUX_RESOLUTION ;
} 
/*=========================================================================================================================================
 * @brief     Get Data Directly 
 * @param     BU27006MUCZ       GebraBit_BU27006MUCZ Struct
 * @return    Nothing
 ========================================================================================================================================*/ 
void GB_BU27006MUCZ_Get_Data(GebraBit_BU27006MUCZ * BU27006MUCZ)
{
  GB_BU27006MUCZ_Read_RGB_IR_FLICKER( BU27006MUCZ );
	GB_BU27006MUCZ_Color_Luminosity(BU27006MUCZ);
}
/*----------------------------------------------------------------------------------------------------------------------------------------*
 *                                                                      End                                                               *
 *----------------------------------------------------------------------------------------------------------------------------------------*/
//	GB_BU27006MUCZ_Write_Reg_Data(BU27006MUCZ_ALS_THRES_UP_0, 0x0A)	;
//	GB_BU27006MUCZ_Write_Reg_Data(BU27006MUCZ_ALS_THRES_UP_1, 0x0B)	;
//	GB_BU27006MUCZ_Write_Reg_Data(BU27006MUCZ_ALS_THRES_UP_2, 0x0C)	;
//  GB_BU27006MUCZ_Read_Reg_Data (BU27006MUCZ_ALS_MEAS_RATE,&BU27006MUCZ_Module.Register_Cache);
//	GB_BU27006MUCZ_Read_Reg_Data (BU27006MUCZ_ALS_GAIN,&BU27006MUCZ_Module.Register_Cache);
//	GB_BU27006MUCZ_Read_Reg_Data (BU27006MUCZ_PART_ID,&BU27006MUCZ_Module.Register_Cache);
//	GB_BU27006MUCZ_Read_Reg_Data (BU27006MUCZ_MAIN_STATUS,&BU27006MUCZ_Module.Register_Cache);
//	GB_BU27006MUCZ_Read_Reg_Data (BU27006MUCZ_INT_CFG,&BU27006MUCZ_Module.Register_Cache);
//	HAL_I2C_Mem_Write(BU27006MUCZ_I2C,BU27006MUCZ_WRITE_ADDRESS,BU27006MUCZ_ALS_THRES_UP_0,1,data,3,200);
//	GB_BU27006MUCZ_Burst_Read( BU27006MUCZ_ALS_THRES_UP_0 , BU27006MUCZ_Module.REGISTER_DATA , 3);