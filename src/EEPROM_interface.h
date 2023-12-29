/*
 * EEPROM_interface.h
 *
 * Created: 12/15/2023 5:49:05 PM
 *  Author: Mazen
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


#define EEPROM_ADDRESS	0x50

void EEPROM_Vid_Write_Byte(u16 copy_u16_address, u8 copy_u8_data);
void EEPROM_Vid_Write_Page(u16 copy_u16_address, u8* copy_c8_data);
u8 EEPROM_u8_Read_Byte(u16 copy_u16_address);
void EEPROM_Vid_Write_String(u16 copy_u16_address, u8* copy_u8_string);
c8* EEPROM_Read_String(u16 copy_u16_address);

#endif /* EEPROM_INTERFACE_H_ */