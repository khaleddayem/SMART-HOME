/*
 * Check_file.c
 *
 * Created: 12/29/2023 10:48:54 AM
 *  Author: mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_INT_interface.h"
#include "Timer0_interface.h"
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "LCD_interface.h"
#include "Admin_interface.h"

u16 GLO_u16_Air;
extern u8 GLO_u8_Num_Users;
u32 GLO_u32_Temp = 0;
u8 GLO_u8_Flag = 0;

u8 CHECK_PASSWORD(u8 copy_u8_address, u8* copy_u8_check){
	u8 LOC_u8_In = 0;
	while(1){
		if(EEPROM_u8_Read_Byte(copy_u8_address) == copy_u8_check[LOC_u8_In]){
			LOC_u8_In++;
			copy_u8_address++;
			if(LOC_u8_In == 6){
				return 1;
			}
		}
		else{
			return 0;
		}
	}
}
/***************************************************************************************************/
u32 CHECK_Username(c8* copy_c8_check){
	u16 LOC_u16_Address = 0x20;
	u8 LOC_u8_Copy_Address;
	u8 LOC_u8_In = 0;
	s8 LOC_s8_In = 0;
	for(LOC_s8_In = 0; LOC_s8_In < GLO_u8_Num_Users; LOC_s8_In++){
		if(EEPROM_u8_Read_Byte(LOC_u16_Address) != 0xff){
			if (EEPROM_u8_Read_Byte(LOC_u16_Address) == copy_c8_check[LOC_u8_In])
			{
				LOC_u8_In++;
				LOC_u8_Copy_Address = LOC_u16_Address + 1;
				while(1){
					if(EEPROM_u8_Read_Byte(LOC_u8_Copy_Address) == copy_c8_check[LOC_u8_In]){
						LOC_u8_In++;
						LOC_u8_Copy_Address++;
						if (EEPROM_u8_Read_Byte(LOC_u8_Copy_Address) == 0xff && copy_c8_check[LOC_u8_In] == '\0')
						{
							return LOC_u16_Address;
						}
					}
					else{
						LOC_u16_Address += 0x20;
						break;
					}
				}
				LOC_u8_In = 0;
			}
			else{
				LOC_u16_Address += 0x20;
			}
		}
		else{
			LOC_u16_Address += 0x20;
			LOC_s8_In--;
		}
	}
	return 0;
}

/***************************************************************************************************/

u16 Is_Memory_Full(void){
	u16 LOC_u16_Address = 0x20;
	while(1){
		if(EEPROM_u8_Read_Byte(LOC_u16_Address) != 0xff){
			LOC_u16_Address += 0x20;
			if(LOC_u16_Address == 0x200){
				return 1;
			}
		}
		else{
			return LOC_u16_Address;
		}
	}
}
/***************************************************************************************************/
u8 Only_Numbers(u8* copy_u8_password){
	u8 LOC_u8_In;
	for (LOC_u8_In = 0 ; LOC_u8_In < 6; LOC_u8_In++)
	{
		if(copy_u8_password[LOC_u8_In] < '0' || copy_u8_password[LOC_u8_In] > '9'){
			return 1;
		}
	}
	return 0;
}
/***************************************************************************************************/
void Num_of_Users(void){
	u16 LOC_u16_Address = 0x20;
	while(1){
		if(EEPROM_u8_Read_Byte(LOC_u16_Address) != 0xff){
			GLO_u8_Num_Users++;
		}
		LOC_u16_Address += 0x20;
		if(LOC_u16_Address == 0x200){
			return;
		}
	}
}
/***************************************************************************************************/

u8 CHECK_Username_In_Sys(u8 copy_u8_data){
	u16 LOC_u16_Address = 0x38;
	s8 LOC_s8_In = 0;
	for(LOC_s8_In = 0; LOC_s8_In < GLO_u8_Num_Users; LOC_s8_In++){
		if(EEPROM_u8_Read_Byte(LOC_u16_Address) != 0xff){
			if (EEPROM_u8_Read_Byte(LOC_u16_Address) == copy_u8_data)
			{
				return LOC_u16_Address;
			}
			else{
				LOC_u16_Address += 0x20;
			}
		}
		else{
			LOC_u16_Address += 0x20;
			LOC_s8_In--;
		}
	}
	return 0;
}
/***************************************************************************************************/
void Check_Temp(void){
	GLO_u8_Flag = 1;
	GLO_u32_Temp = ADC_READ();
	GLO_u32_Temp = ((GLO_u32_Temp*500)/(1023));
	if(GLO_u32_Temp > 28)
	{
		DIO_Vid_Set_Pin_Val(PORTA,PIN3,HIGH);
	}
	else if(GLO_u32_Temp < 21)
	{
		DIO_Vid_Set_Pin_Val(PORTA,PIN3,LOW);
	}
	else{}
}