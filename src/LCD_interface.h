/*
 * LCD_interface.h
 *
 * Created: 9/7/2023 6:13:58 PM
 *  Author: mazen
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_MODE	FOUR_BIT
#define EIGHT_BIT	0
#define FOUR_BIT	1
/*****************************************************************************
* Function Name: LCD_Vid_Send_Command
* Purpose      : Send command to LCD
* Parameters   : copy_u8_command
* Return value : void
*****************************************************************************/
void LCD_Vid_Send_Command(u8 copy_u8_command);
/*****************************************************************************
* Function Name: LCD_Vid_Send_Data
* Purpose      : Send data  to LCD
* Parameters   : copy_u8_data
* Return value : void
*****************************************************************************/
void LCD_Vid_Send_Data(u8 copy_u8_data);
/*****************************************************************************
* Function Name: LCD_Vid_Init
* Purpose      : initialized LCD
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_Vid_Init(void);
/*****************************************************************************
* Function Name: LCD_Vid_Send_String
* Purpose      : Display string on LCD
* Parameters   : c8* copy_c8_string
* Return value : void
*****************************************************************************/
void LCD_Vid_Send_String(c8* copy_c8_string);
/*****************************************************************************
* Function Name: LCD_Vid_Send_Num
* Purpose      : Display Number on LCD
* Parameters   : u32 copy_u32_num
* Return value : void
*****************************************************************************/
void LCD_Vid_Send_Num(u32 copy_u32_num);
/*****************************************************************************
* Function Name: LCD_Vid_GOTOXY
* Purpose      : Send address of x & y to write on this address
* Parameters   : u8 copy_u8_x, u8 copy_u8_y
* Return value : void
*****************************************************************************/
void LCD_Vid_GOTOXY(u8 copy_u8_x, u8 copy_u8_y);
/*****************************************************************************
* Function Name: LCD_Vid_Draw_Data
* Purpose      : Create A new character on LCD
* Parameters   : u8 copy_u8_pattern, u8* copy_u8_data, u8 copy_u8_x, u8 copy_u8_y
* Return value : void
*****************************************************************************/
void LCD_Vid_Draw_Data(u8 copy_u8_pattern, u8* copy_u8_data, u8 copy_u8_x, u8 copy_u8_y);

#define DATA_LENGTH 4
#define MOD_10(NUM) (NUM%10)
#define DIV_BY_10(NUM) (NUM/10)
#define ASCII_OF_0 48

#endif /* LCD_INTERFACE_H_ */