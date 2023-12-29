/*
 * Admin_interface.c
 *
 * Created: 12/28/2023 5:11:25 PM
 *  Author: mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_INT_interface.h"
#include "Timer0_interface.h"
#include "Timer1_interface.h"
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "KEYPAD_interface.h"
#include "LCD_interface.h"
#include "Check_file.h"
#include "Admin_interface.h"
#define F_CPU 16000000UL
#include "util/delay.h"

u8 GLO_u8_permission = 0;
u8 GLO_u8_Num_Users;
extern u8 GLO_u8_Dim_dutyCycle;

void Admin_Mode_Login(void){
	GLO_u8_permission = 1;
	u8 LOC_u8_Check = 9;
	u8 LOC_u8_Attempts = 3;
	u8 LOC_u8_Arr[10];
	u8 LOC_u8_In = 0;
	u8 LOC_u8_Key = 0xff;
	UART_Vid_Tx_String("\nEnter Password (6 Digits): \n");
	while(LOC_u8_Attempts){
		LOC_u8_Key = UART_u8_Rx();
		if(LOC_u8_Key >= 32 || LOC_u8_Key <= 126){
			if(LOC_u8_Key != '&'){
				LOC_u8_Arr[LOC_u8_In] = LOC_u8_Key;
				LOC_u8_In++;
			}
			if(LOC_u8_Key == '&'){
				if(LOC_u8_In == 6){
					LOC_u8_Check = CHECK_PASSWORD(0x00,LOC_u8_Arr);
				}
				else{
					UART_Vid_Tx_String("\nPassword is not 6 digits\n");
					LOC_u8_Attempts--;
					UART_Vid_Tx_String("\nRemaining Attempts: ");
					UART_Vid_Tx(LOC_u8_Attempts + ASCII_OF_0);
					UART_Vid_Tx('\n');
					if(LOC_u8_Attempts > 0){
						UART_Vid_Tx_String("\nEnter Password (6 Digits): \n");
					}
				}
				LOC_u8_In = 0;
				if(LOC_u8_Check == 1){
					UART_Vid_Tx_String("\nWelcome Admin\n");
					Admin_Mode_Control();
					return;
				}
				else if(LOC_u8_Check == 0){
					UART_Vid_Tx_String("\nWrong Password !!!\n");
					LOC_u8_Attempts--;
					UART_Vid_Tx_String("\nRemaining Attempts: ");
					UART_Vid_Tx(LOC_u8_Attempts + ASCII_OF_0);
					UART_Vid_Tx('\n');
					if(LOC_u8_Attempts > 0){
						UART_Vid_Tx_String("\nEnter Password (6 Digits): \n");
					}
					LOC_u8_Check = 9;
				}
				
			}
			LOC_u8_Key = 0xff;
		}
	}
	DIO_Vid_Set_Pin_Val(PORTA,PIN1,HIGH);
	UART_Vid_Tx_String("\nYou have used all your attempts \n");
	GLO_u8_permission = 0;
	while (1);
}
/**************************************************************************************************/
void Admin_Mode_Control(void){
	
	u8 LOC_u8_Key = 0xff;
	while (1)
	{
		LOC_u8_Key = UART_u8_Rx();
		switch (LOC_u8_Key)
		{
			case 'A':	DIO_Vid_Toggle_Pin_Val(PORTD, PIN3);
						break;
			case 'B':	DIO_Vid_Toggle_Pin_Val(PORTD, PIN6);
						break;
			case 'C':	DIO_Vid_Toggle_Pin_Val(PORTD, PIN7);
						break;
			case 'D':	DIO_Vid_Toggle_Pin_Val(PORTC, PIN6);
						break;
			case 'E':	DIO_Vid_Toggle_Pin_Val(PORTC, PIN7);
						break;
			case 'F':	if (GLO_u8_Dim_dutyCycle == 90)
						{
							UART_Vid_Tx_String("\nMAX BRIGHTNESS !!\n");
						}
						else
						{
							GLO_u8_Dim_dutyCycle += 10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case 'G':	if (GLO_u8_Dim_dutyCycle == 0)
						{
							UART_Vid_Tx_String("\nMIN BRIGHTNESS !!\n");
						}
						else
						{
							GLO_u8_Dim_dutyCycle -= 10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case 'H':	TIM1_Vid_FastPWM_Mode14(1000,14);
						UART_Vid_Tx_String("\nDoor is open\n");	
						break;
			case 'K':	TIM1_Vid_FastPWM_Mode14(1000,2);
						UART_Vid_Tx_String("\nDoor is closed\n");
						break;
			case 'I':	Admin_Mode_Register();
						break;
			case 'J':	UART_Vid_Tx_String("\nGOODBYE\n");
						GLO_u8_permission = 0;
						return;
			case 0xff: break;
			default:	UART_Vid_Tx_String("\nWRONG INPUT\n");
		}
	}
	return;
}
/**************************************************************************************************/

void Admin_Mode_Register(void){
	c8 LOC_c8_Username[15] = {0};
	u8 LOC_u8_Password[10] = {0};
	u8 LOC_u8_Username_Sys = 0xff;
	u8 LOC_u8_In = 0;
	u16 LOC_u16_Empty;
	u16 LOC_u16_Address;
	u8 LOC_u8_Full;
	u8 LOC_u8_Key = 0xff;
	UART_Vid_Tx_String("\nTo add a user (Press 1)\nTo delete a user (Press 2):\n");
	while(1){
		LOC_u8_Key = UART_u8_Rx();
		if (LOC_u8_Key == '1')
		{
			LOC_u8_Full = Is_Memory_Full();
			if(LOC_u8_Full == 1){
				UART_Vid_Tx_String("\nMemory is full\n");
				return;
			}
			else{
				LOC_u16_Empty = LOC_u8_Full;
			}
			UART_Vid_Tx_String("\nEnter Username for the remoting system:\n(First name only)\n");
			while (1)
			{
				LOC_u8_Key = UART_u8_Rx();
				if(LOC_u8_Key >= 32 || LOC_u8_Key <= 126){
					if(LOC_u8_Key != '&'){
						LOC_c8_Username[LOC_u8_In] = LOC_u8_Key;
						LOC_u8_In++;
					}
					if(LOC_u8_Key == '&'){
						LOC_u8_In = 0;
						LOC_u16_Address = CHECK_Username(LOC_c8_Username);
						if(LOC_u16_Address != 0)
						{
							UART_Vid_Tx_String("\nThis user is already existed\n");
							return;
						}
						else{
							if(LOC_c8_Username[0] < 65 || LOC_c8_Username[0] > 90){
								UART_Vid_Tx_String("\nFirst letter should be capital !!\n");
								LCD_Vid_GOTOXY(0,0);
								LCD_Vid_Send_String(LOC_c8_Username);
								LOC_u8_In = 0;
							}
							else{
								EEPROM_Vid_Write_String(LOC_u16_Empty,LOC_c8_Username);
								break;
							}
						}
					}
					LOC_u8_Key = 0xff;
				}
			}
			LOC_u8_In = 0;
			LOC_u8_Key = 0xff;
			UART_Vid_Tx_String("\nEnter Password (6 Digits): \n");
			while (1)
			{
				LOC_u8_Key = UART_u8_Rx();
				if(LOC_u8_Key >= 32 || LOC_u8_Key <= 126){
					if(LOC_u8_Key != '&'){
						LOC_u8_Password[LOC_u8_In] = LOC_u8_Key;
						LOC_u8_In++;
					}
					if(LOC_u8_Key == '&'){
						if(LOC_u8_In == 6){
							if(Only_Numbers(LOC_u8_Password) == 1){
								UART_Vid_Tx_String("\nPassword should be only numbers\n");
								UART_Vid_Tx_String("\nEnter Password (6 Digits): \n");
							}
							else{
								EEPROM_Vid_Write_String(LOC_u16_Empty + 0x10,LOC_u8_Password);
								break;
							}
						}
						else{
							UART_Vid_Tx_String("\nPassword is not 6 digits\n");
							UART_Vid_Tx_String("\nEnter Password (6 Digits): \n");
							while(LOC_u8_In)
							{
								LOC_u8_Password[LOC_u8_In] = '\0';
								LOC_u8_In--;
							}
						}
						LOC_u8_In = 0;
					}
					LOC_u8_Key = 0xff;
				}
			}
			LOC_u8_In = 0;
			LOC_u8_Key = 0xff;
			UART_Vid_Tx_String("\nEnter Username for this system:\n(Only 1 Number)\n");
			while (1)
			{
				LOC_u8_Key = UART_u8_Rx();
				if(LOC_u8_Key >= 32 || LOC_u8_Key <= 126){
					if(LOC_u8_Key != '&'){
						LOC_u8_Username_Sys= LOC_u8_Key;
						LOC_u8_In++;
					}
					if(LOC_u8_Key == '&'){
						if(LOC_u8_In == 1){
							if(LOC_u8_Username_Sys < '1' || LOC_u8_Username_Sys > '9'){
								UART_Vid_Tx_String("\nUsername should be only numbers (1 -> 9)\n");
								UART_Vid_Tx_String("\nEnter Username for this system:\n(Only 1 Number)\n");
							}
							else{
								LOC_u16_Address = 0x38;
								while (LOC_u16_Address != 0x218)
								{
									if(EEPROM_u8_Read_Byte(LOC_u16_Address) == LOC_u8_Username_Sys){
										UART_Vid_Tx_String("\nThis Username is already used\n");
										UART_Vid_Tx_String("\nEnter another Username for this system:\n(Only 1 Number)\n");
										break;
									}
									LOC_u16_Address += 0x20;
								}
								if (LOC_u16_Address == 0x218)
								{
									EEPROM_Vid_Write_Byte(LOC_u16_Empty + 0x18,LOC_u8_Username_Sys);
									UART_Vid_Tx_String("\nUser has been added successfully\n");
									GLO_u8_Num_Users++;
									return;
								}
							}
						}
						else{
							UART_Vid_Tx_String("\nUsername is not 1 number only\n");
							UART_Vid_Tx_String("\nEnter Username for this system:\n(Only 1 Number)\n");
						}
						LOC_u8_In = 0;
					}
					LOC_u8_Key = 0xff;
				}
			}
		}
		else if (LOC_u8_Key == '2')
		{
			UART_Vid_Tx_String("\nEnter Username you want to delete:\n");
			while (1)
			{
				LOC_u8_Key = UART_u8_Rx();
				if(LOC_u8_Key >= 32 || LOC_u8_Key <= 126){
					if(LOC_u8_Key != '&'){
						LOC_c8_Username[LOC_u8_In] = LOC_u8_Key;
						LOC_u8_In++;
					}
					if(LOC_u8_Key == '&'){
						LOC_u8_In = 0;
						LOC_u16_Address = CHECK_Username(LOC_c8_Username);
						if(LOC_u16_Address == 0)
						{
							if(LOC_c8_Username[0] < 65 || LOC_c8_Username[0] > 90){
								UART_Vid_Tx_String("\nFirst letter should be capital !!\n");
							}
							else{
								UART_Vid_Tx_String("\nThis user is not existed\n");
								return;
							}
						}
						else{
							u16 LOC_u16_Max = LOC_u16_Address + 0x20;
							for (LOC_u16_Address ;LOC_u16_Address < LOC_u16_Max;LOC_u16_Address++)
							{
								EEPROM_Vid_Write_Byte(LOC_u16_Address,0xff);
							}
							UART_Vid_Tx_String("\nUser has been deleted successfully\n");
							GLO_u8_Num_Users--;
							return;
						}
					}
					LOC_u8_Key = 0xff;
				}
			}
		}
		else{
			UART_Vid_Tx_String("\nYou neither press 1 nor 2\n");
			return;
		}
	}
}