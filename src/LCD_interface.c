/*
 * LCD_interface.c
 *
 * Created: 9/7/2023 6:13:42 PM
 *  Author: mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#define F_CPU 16000000UL
#include "util/delay.h"

static void SHDATA(u8 copy_u8_data){
	u8 LOC_u8_LCD_PINS[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN};
	u8 LOC_u8_IN = 0;
	for(LOC_u8_IN = 0; LOC_u8_IN < DATA_LENGTH; LOC_u8_IN++){
		DIO_Vid_Set_Pin_Val(LCD_DPORT,LOC_u8_LCD_PINS[LOC_u8_IN],GET_BIT(copy_u8_data,LOC_u8_IN));
	}
}
static void Send_Enable(){
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_EN_PIN,HIGH);
	_delay_ms(2);
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_EN_PIN,LOW);
}
void LCD_Vid_Send_Command(u8 copy_u8_command){
	/* SET RS --> LOW TO SEND COMMAND */
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RS_PIN,LOW);
	/* SET RW --> LOW TO WRITE ON LCD */
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RW_PIN,LOW);
	/* SEND COMMAND */
	#if LCD_MODE == EIGHT_BIT
	DIO_Vid_Set_Port_Val(LCD_DPORT,copy_u8_command);
	/* SEND PULSE */
	Send_Enable();
	#elif LCD_MODE == FOUR_BIT
	/* SEND HSB COMMAND */
	SHDATA(copy_u8_command>>4);
	/* SEND PULSE */
	Send_Enable();
	/* SEND LSB COMMAND */
	SHDATA(copy_u8_command);
	/* SEND PULSE */
	Send_Enable();
	#endif
}

void LCD_Vid_Send_Data(u8 copy_u8_data){
	/* SET RS --> HIGH TO SEND DATA */
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RS_PIN,HIGH);
	/* SET RW --> LOW TO WRITE ON LCD */
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RW_PIN,LOW);
	/* SEND DATA */
	#if LCD_MODE == EIGHT_BIT
	DIO_Vid_Set_Port_Val(LCD_DPORT,copy_u8_data);
	/* SEND PULSE */
	Send_Enable();
	#elif LCD_MODE == FOUR_BIT
	/* SEND HSB DATA */
	SHDATA(copy_u8_data>>4);
	/* SEND PULSE */
	Send_Enable();
	/* SEND LSB DATA */
	SHDATA(copy_u8_data);
	/* SEND PULSE */
	Send_Enable();
	#endif
}

void LCD_Vid_Init(void){
	_delay_ms(40);
	#if LCD_MODE == EIGHT_BIT
	/* SEND FUNCTION SET ( N = 1 ---> ENABLE 2 LINE / F = 0 font(5*7) ) */
	LCD_Vid_Send_Command(0b00111000);
	#elif LCD_MODE == FOUR_BIT
	/* SEND FUNCTION SET ( N = 1 ---> ENABLE 2 LINE / F = 0 font(5*7) ) */
	SHDATA(0b0010);
	Send_Enable();
	SHDATA(0b0010);
	Send_Enable();
	SHDATA(0b1000);
	Send_Enable();
	#endif
	/* DISPLAY ON/OFF CONTROL */
	LCD_Vid_Send_Command(0b00001100);
	/* SEND CLEAR */
	LCD_Vid_Send_Command(0x01);
}

void LCD_Vid_Send_String(c8* copy_c8_string){
	u8 LOC_u8_Counter = 0;
	while(copy_c8_string[LOC_u8_Counter] != '\0'){
		LCD_Vid_Send_Data(copy_c8_string[LOC_u8_Counter]);
		LOC_u8_Counter++;
	}
}

void LCD_Vid_Send_Num(u32 copy_u32_num){
	s8 LOC_u8_In = 0;
	u8 LOC_u8_Count = 0;
	u8 LOC_u8_All_Digits[10]={ASCII_OF_0};
	while(copy_u32_num>0){
		LOC_u8_All_Digits[LOC_u8_Count] = MOD_10(copy_u32_num) + ASCII_OF_0;
		copy_u32_num = DIV_BY_10(copy_u32_num);
		LOC_u8_Count++;
	}
	if(LOC_u8_Count == 0){
		LOC_u8_Count++;
	}
	for(LOC_u8_In = (LOC_u8_Count-1); LOC_u8_In >= 0; LOC_u8_In--)
		LCD_Vid_Send_Data(LOC_u8_All_Digits[LOC_u8_In]);
}

void LCD_Vid_GOTOXY(u8 copy_u8_x, u8 copy_u8_y){
	
	u8 LOC_u8_AddDDRAM = 0;
	if(copy_u8_y == 0){
		LOC_u8_AddDDRAM = copy_u8_x;
	}
	else if(copy_u8_y == 1){
		LOC_u8_AddDDRAM = copy_u8_x + 0x40;
	}
	/* LOC_u8_AddDDRAM = copy_u8_x + copy_u8_y * 0x40 */
	/* SET DDRAM ADDRESS */
	SET_BIT(LOC_u8_AddDDRAM,PIN7);
	LCD_Vid_Send_Command(LOC_u8_AddDDRAM);
}

void LCD_Vid_Draw_Data(u8 copy_u8_pattern, u8* copy_u8_data, u8 copy_u8_x, u8 copy_u8_y){
	
	u8 LOC_u8_IN = 0;
	/* CALCULATE ADDRESS IN CGRAM */
	u8 LOC_u8_AddCGRAM = copy_u8_pattern * 8;
	/* SET CGRAM */
	CLR_BIT(LOC_u8_AddCGRAM,PIN7);
	SET_BIT(LOC_u8_AddCGRAM,PIN6);
	LCD_Vid_Send_Command(LOC_u8_AddCGRAM);
	/* DRAW DATA IN CGRAM */
	for(LOC_u8_IN = 0; LOC_u8_IN < 8; LOC_u8_IN++){
		LCD_Vid_Send_Data(copy_u8_data[LOC_u8_IN]);
	}
	/* SET DDRAM ADDRESS */
	LCD_Vid_GOTOXY(copy_u8_x,copy_u8_y);
	
	LCD_Vid_Send_Data(copy_u8_pattern);
	
}