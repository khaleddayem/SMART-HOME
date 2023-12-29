/*
 * EEPROM_interface.c
 *
 * Created: 12/15/2023 5:48:55 PM
 *  Author: Mazen
 */ 
 

#include "STD_TYPE.h" 
#include "BIT_MATH.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void EEPROM_Vid_Write_Byte(u16 copy_u16_address, u8 copy_u8_data){
	
	u8 LOC_u8_Address = (copy_u16_address >> 8) | EEPROM_ADDRESS;
	/* Send Start Condition */
	TWI_Send_Start_Condition();
	/* Send the Address Packet + Write */
	TWI_Send_Slave_Address_With_Write(LOC_u8_Address);
	/* Send the LSB of the Location Address */
	TWI_Master_Send_Data((u8)copy_u16_address);
	/* Send the Data */
	TWI_Master_Send_Data(copy_u8_data);
	/* Send Stop Condition */
	TWI_Vid_Send_Stop_Condition();
	
	_delay_ms(5);
	
}

void EEPROM_Vid_Write_Page(u16 copy_u16_address, u8* copy_u8_data){
	
	u32 LOC_u32_In = 0;
	u8 LOC_u8_Address = (copy_u16_address >> 8) | EEPROM_ADDRESS;
	/* Send Start Condition */
	TWI_Send_Start_Condition();
	/* Send the Address Packet + Write */
	TWI_Send_Slave_Address_With_Write(LOC_u8_Address);
	/* Send the LSB of the Location Address */
	TWI_Master_Send_Data((u8)copy_u16_address);
	while(copy_u8_data[LOC_u32_In] != '\0'){
		/* Send the Data */
		TWI_Master_Send_Data(copy_u8_data[LOC_u32_In]);
		LOC_u32_In++;
	}
	/* Send Stop Condition */
	TWI_Vid_Send_Stop_Condition();
	
	_delay_ms(5);
	
}


u8 EEPROM_u8_Read_Byte(u16 copy_u16_address){
	
	u8 LOC_u8_Data = 0;
	u8 LOC_u8_Address = (copy_u16_address >> 8) | EEPROM_ADDRESS;
	/* Send Start Condition */
	TWI_Send_Start_Condition();
	/* SEND the Address Packet + Write */
	TWI_Send_Slave_Address_With_Write(LOC_u8_Address);
	/* Send the LSB of the Location Address */
	TWI_Master_Send_Data((u8)copy_u16_address);
	/* Send Repeated Start */
	TWI_Repeated_Start_Condition();
	/* Send the Address Packet Again + Read */
	TWI_Send_Slave_Address_With_Read(LOC_u8_Address);
	/* Master Read Data */
	TWI_Master_Receive_Data(&LOC_u8_Data);
	/* Send Stop Condition */
	TWI_Vid_Send_Stop_Condition();
	
	_delay_ms(5);
	
	return LOC_u8_Data;
	
}

void EEPROM_Vid_Write_String(u16 copy_u16_address, u8* copy_u8_string){
	u8 LOC_u8_Counter = 0;
	while(copy_u8_string[LOC_u8_Counter] != '\0'){
		EEPROM_Vid_Write_Byte(copy_u16_address,copy_u8_string[LOC_u8_Counter]);
		copy_u16_address++;
		LOC_u8_Counter++;
	}
}


c8 LOC_u8_arr[15];
c8* EEPROM_Read_String(u16 copy_u16_address){
	
	if(EEPROM_u8_Read_Byte(copy_u16_address) == 0xff){
		return 0;
	}
	c8 LOC_c8_Char;
	u8 LOC_u8_In = 0;
	while(1){
		LOC_c8_Char = EEPROM_u8_Read_Byte(copy_u16_address);
		LOC_u8_arr[LOC_u8_In] = LOC_c8_Char;
		copy_u16_address++;
		LOC_u8_In++;
		if(EEPROM_u8_Read_Byte(copy_u16_address) == 0xff){
			for ( ; LOC_u8_In < 15; LOC_u8_In++)
			{
				LOC_u8_arr[LOC_u8_In] = 0;
			}
			break;
		}
	}
	return LOC_u8_arr;
}