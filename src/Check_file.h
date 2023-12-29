/*
 * Check_file.h
 *
 * Created: 12/29/2023 10:49:08 AM
 *  Author: mazen
 */ 


#ifndef CHECK_FILE_H_
#define CHECK_FILE_H_

u8 CHECK_PASSWORD(u8 copy_u8_address, u8* copy_u8_check);
u32 CHECK_Username(c8* copy_c8_check);
u16 Is_Memory_Full(void);
u8 Only_Numbers(u8* copy_u8_password);
void Num_of_Users(void);
u8 CHECK_Username_In_Sys(u8 copy_u8_data);
void Check_Temp(void);

#endif /* CHECK_FILE_H_ */