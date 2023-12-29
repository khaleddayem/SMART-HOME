/*
 * SMART_HOME.c
 *
 * Created: 12/20/2023 5:27:10 AM
 * Author : mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_INT_interface.h"
#include "TWI_interface.h"
#include "UART_interface.h"
#include "Timer0_interface.h"
#include "Timer1_interface.h"
#include "EEPROM_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "Admin_interface.h"
#include "User_interface.h"
#include "Check_file.h"
#define F_CPU 16000000UL
#include "util/delay.h"





int main(void)
{
	u8 LOC_u8_Key = 0xff;
	u8 LOC_u8_KeyPad = 0xff;
	/* Single pins */
	DIO_Vid_Set_Pin_Dir(PORTA,PIN1,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN3,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN6,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN7,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTC,PIN6,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTC,PIN7,OUTPUT);
	
	 /* Servo PIN Coning */
	DIO_Vid_Set_Pin_Dir(PORTD,PIN4,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN5,OUTPUT);
	TIM1_Vid_FastPWM_Mode14(1000,2);
	/* LCD */
	DIO_Vid_Set_Port_Dir(LCD_DPORT,PORT_OUTPUT);
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RS_PIN,OUTPUT);
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RW_PIN,OUTPUT);
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_EN_PIN,OUTPUT);
	LCD_Vid_Init();
	/* KEYPAD */
	KEYPAD_Vid_Init();
	/* UART */
	UART_Vid_Init();
	
	/*	ADC	*/
	ADC_Vid_Init();
	ADC_Vid_Int_Setcallback(Check_Temp);
	DIO_Vid_Set_Pin_Dir(PORTA,PIN3,OUTPUT);
	/* TWI */
	TWI_Vid_Master_Init(0) ;
	/* Calculate Number Of Users In The System */
	Num_of_Users();
	
	LCD_Vid_GOTOXY(0,0);
	LCD_Vid_Send_String("Waiting - Press 'C' for login");
	UART_Vid_Tx_String("\nSystem is waiting (Press 'Login')\n");
	
	while (1) 
    {
		LOC_u8_KeyPad = KEYPAD_u8_Get_Key();
		LOC_u8_Key = UART_u8_Rx_Control();
		if (LOC_u8_Key == 'Z')
		{
			LCD_Vid_Send_Command(0x01);
			LCD_Vid_GOTOXY(0,0);
			LCD_Vid_Send_String("Admin/User is trying to login remotely");
			UART_Vid_Tx_String("\nChoose Mode:\n");
			UART_Vid_Tx_String("Admin Mode\n");
			UART_Vid_Tx_String("User Mode\n");
			while(1){
				LOC_u8_Key = UART_u8_Rx_Control();
				if(LOC_u8_Key == '1'){
					LCD_Vid_Send_Command(0x01);
					LCD_Vid_GOTOXY(0,0);
					LCD_Vid_Send_String("Admin is online");
					/* Admin Login Remote */
					Admin_Mode_Login();
					UART_Vid_Tx_String("\nSystem is waiting (Press 'Wake')\n");
					LCD_Vid_Send_Command(0x01);
					LCD_Vid_GOTOXY(0,0);
					LCD_Vid_Send_String("Waiting - Press 'C' for login");
					break;
				}
				
				else if(LOC_u8_Key == '2'){
					LCD_Vid_Send_Command(0x01);
					LCD_Vid_GOTOXY(0,0);
					LCD_Vid_Send_String("A user is trying to login remotely");
					/* User Login Remote */
					User_Mode_Login();
					UART_Vid_Tx_String("\nSystem is waiting (Press 'Login')\n");
					LCD_Vid_Send_Command(0x01);
					LCD_Vid_GOTOXY(0,0);
					LCD_Vid_Send_String("Waiting - Press 'C' for login");
					break;
				}
				else if(LOC_u8_Key != 0xff){
					UART_Vid_Tx_String("\nWRONG INPUT !!!\n");
				}
			}
		}
		else if(LOC_u8_Key != 0xff){
			UART_Vid_Tx_String("\nSystem is waiting (Press 'Login')\n");
		}
		if(LOC_u8_KeyPad == 'C'){
			/* User Login Using Keypad & LCD */
			User_Mode_Login_KeyPad();
			UART_Vid_Tx_String("\nSystem is waiting (Press 'Login')\n");
			LCD_Vid_Send_Command(0x01);
			LCD_Vid_GOTOXY(0,0);
			LCD_Vid_Send_String("Waiting - Press 'C' for login");
		}
    }
}




