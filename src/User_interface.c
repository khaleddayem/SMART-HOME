/*
 * User_interface.c
 *
 * Created: 12/29/2023 10:42:40 AM
 *  Author: mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_INT_interface.h"
#include "Timer0_interface.h"
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "KEYPAD_interface.h"
#include "LCD_interface.h"
#include "Check_file.h"
#include "Admin_interface.h"
#include "User_interface.h"
#define F_CPU 16000000UL
#include "util/delay.h"

extern u8 GLO_u8_permission;
extern u8 GLO_u8_Num_Users;
extern u32 GLO_u32_Temp;
extern u8 GLO_u8_Flag;
u8 GLO_u8_Dim_dutyCycle = 0;
u8 GLO_u8_Star[8] = { 0x04,0x04,0x15,0x0E,0x0E,0x0E,0x15,0x04};

void User_Mode_Login(void){
	if(GLO_u8_permission == 1){
		UART_Vid_Tx_String("\nThe administrator is online\n");
		return;
	}
	c8 LOC_c8_Arr[15] = {0};
	u8 LOC_u8_Attempts = 3;
	u8 LOC_u8_Key = 0xff;
	u8 LOC_u8_In = 0;
	u16 LOC_u16_Check = 0x200;
	if (GLO_u8_Num_Users == 0)
	{
		UART_Vid_Tx_String("\nThere are no users in the system\n");
		return;
	}
	UART_Vid_Tx_String("\nEnter your username:\n");
	while(LOC_u8_Attempts){
		LOC_u8_Key = UART_u8_Rx();
		if(LOC_u8_Key >= 32 || LOC_u8_Key <= 126){
			if(LOC_u8_Key != '&'){
				LOC_c8_Arr[LOC_u8_In] = LOC_u8_Key;
				LOC_u8_In++;
			}
			if(LOC_u8_Key == '&'){
				LOC_u16_Check = CHECK_Username(LOC_c8_Arr);
				LOC_u8_In = 0;
				if(LOC_u16_Check != 0 && LOC_u16_Check != 0x200){
					u8 LOC_u8_Check = 9;
					u8 LOC_u8_Arr[10];
					LOC_u8_In = 0;
					LOC_u8_Key = 0xff;
					LOC_u8_Attempts = 3;
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
									LOC_u8_Check = CHECK_PASSWORD(LOC_u16_Check + 0x10,LOC_u8_Arr);
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
									UART_Vid_Tx_String("\nWelcome ");
									UART_Vid_Tx_String(EEPROM_Read_String(LOC_u16_Check));
									UART_Vid_Tx('\n');
									LCD_Vid_Send_Command(0x01);
									LCD_Vid_GOTOXY(0,0);
									LCD_Vid_Send_String(EEPROM_Read_String(LOC_u16_Check));
									LCD_Vid_Send_String(" is controlling from remote");
									User_Mode_Control();
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
				}
				else if(LOC_u16_Check == 0){
					UART_Vid_Tx_String("\nThere is no username with this name !!!\n");
					for(u8 LOC_u8_Iteration = 0; LOC_u8_Iteration < 15; LOC_u8_Iteration++){
						LOC_c8_Arr[LOC_u8_Iteration] = 0;
				}
				LOC_u8_Attempts--;
				UART_Vid_Tx_String("\nRemaining Attempts: ");
				UART_Vid_Tx(LOC_u8_Attempts + ASCII_OF_0);
				UART_Vid_Tx('\n');
					if(LOC_u8_Attempts > 0){
						UART_Vid_Tx_String("\nEnter your username again:\n");
					}
					LOC_u16_Check = 0x200;
				}
				
			}
			LOC_u8_Key = 0xff;
		}
	}
	DIO_Vid_Set_Pin_Val(PORTA,PIN1,HIGH);
	UART_Vid_Tx_String("\nYou have used all your attempts \n");
	while (1);
}
/**************************************************************************************************/
void User_Mode_Login_KeyPad(void){
	u8 LOC_u8_Username = 0;
	u8 LOC_u8_Attempts = 3;
	u8 LOC_u8_Key = 0xff;
	u8 LOC_u8_In = 0;
	u16 LOC_u16_Check = 0x200;
	if (GLO_u8_Num_Users == 0)
	{
		LCD_Vid_Send_Command(0x01);
		LCD_Vid_GOTOXY(0,0);
		LCD_Vid_Send_String("There is no users in this system");
		return;
	}
	LCD_Vid_Send_Command(0x01);
	LCD_Vid_GOTOXY(0,0);
	LCD_Vid_Send_String("Enter your username:");
	LCD_Vid_GOTOXY(0,1);
	while(LOC_u8_Attempts){
		LOC_u8_Key = KEYPAD_u8_Get_Key();
		if(LOC_u8_Key != 0xff && LOC_u8_Key != '='){
			LOC_u8_Username = LOC_u8_Key;
			LCD_Vid_Send_Data(LOC_u8_Key);
			LOC_u8_In++;
		}
		if(LOC_u8_Key == '='){
			if (LOC_u8_In != 1){
				LOC_u8_Attempts --;
				LCD_Vid_Send_Command(0x01);
				LCD_Vid_GOTOXY(0,0);
				LCD_Vid_Send_String("Username should be 1 digit only");
				LCD_Vid_GOTOXY(0,1);
				LCD_Vid_Send_String("Remaining Attempts: ");
				LCD_Vid_Send_Num(LOC_u8_Attempts);
				_delay_ms(1000);
				LCD_Vid_Send_Command(0x01);
				LCD_Vid_GOTOXY(0,0);
				LCD_Vid_Send_String("Enter your username:");
				LCD_Vid_GOTOXY(0,1);
				LOC_u8_In = 0;
			}
			else{
				LOC_u16_Check = CHECK_Username_In_Sys(LOC_u8_Username);
				if(LOC_u16_Check != 0){
					u8 LOC_u8_Check = 9;
					u8 LOC_u8_Arr[10] = {0};
					LOC_u8_In = 0;
					LOC_u8_Key = 0xff;
					LOC_u8_Attempts = 3;
					LCD_Vid_Send_Command(0x01);
					LCD_Vid_GOTOXY(0,0);
					LCD_Vid_Send_String("Enter Password (6 Digits):");
					while(LOC_u8_Attempts){
						LOC_u8_Key = KEYPAD_u8_Get_Key();
						if(LOC_u8_Key != 0xff && LOC_u8_Key != '='){
							LCD_Vid_GOTOXY(LOC_u8_In,1);
							LCD_Vid_Send_Data(LOC_u8_Key);
							_delay_ms(100);
							LCD_Vid_Draw_Data(0,GLO_u8_Star,LOC_u8_In,1);
							LOC_u8_Arr[LOC_u8_In] = LOC_u8_Key;
							LOC_u8_In++;
						}
						if(LOC_u8_Key == '='){
							if(LOC_u8_In == 6){
								LOC_u8_Check = CHECK_PASSWORD(LOC_u16_Check - 0x08,LOC_u8_Arr);
							}
							else{
								LOC_u8_Attempts--;
								LCD_Vid_Send_Command(0x01);
								LCD_Vid_GOTOXY(0,0);
								LCD_Vid_Send_String("Password is not 6 digits");
								LCD_Vid_GOTOXY(0,1);
								LCD_Vid_Send_String("Remaining Attempts: ");
								LCD_Vid_Send_Num(LOC_u8_Attempts);
								_delay_ms(1000);
								if(LOC_u8_Attempts > 0){
									LCD_Vid_Send_Command(0x01);
									LCD_Vid_GOTOXY(0,0);
									LCD_Vid_Send_String("Enter Password (6 Digits):");
								}
							}
							LOC_u8_In = 0;
							if(LOC_u8_Check == 1){
								LCD_Vid_Send_Command(0x01);
								LCD_Vid_GOTOXY(0,0);
								LCD_Vid_Send_String("Welcome:");
								LCD_Vid_GOTOXY(9,0);
								LCD_Vid_Send_String(EEPROM_Read_String(LOC_u16_Check - 0x18));
								UART_Vid_Tx('\n');
								UART_Vid_Tx_String(EEPROM_Read_String(LOC_u16_Check - 0x18));
								UART_Vid_Tx_String(" is controlling from Keypad\n");
								UART_Vid_Tx_String("\nOnly Admin can interrupt\n");
								User_Mode_Control_Keypad();
								return;
							}
							else if(LOC_u8_Check == 0){
								LOC_u8_Attempts--;
								LCD_Vid_Send_Command(0x01);
								LCD_Vid_GOTOXY(0,0);
								LCD_Vid_Send_String("Wrong Password !!!");
								LCD_Vid_GOTOXY(0,1);
								LCD_Vid_Send_String("Remaining Attempts: ");
								LCD_Vid_Send_Num(LOC_u8_Attempts);
								LOC_u8_In = 0;
								_delay_ms(2000);
								if(LOC_u8_Attempts > 0){
									LCD_Vid_Send_Command(0x01);
									LCD_Vid_GOTOXY(0,0);
									LCD_Vid_Send_String("Enter Password (6 Digits):");
								}
								LOC_u8_Check = 9;
							}
						}
						LOC_u8_Key = 0xff;
					}
				}
				else if(LOC_u16_Check == 0){
					LOC_u8_Attempts--;
					LCD_Vid_Send_Command(0x01);
					LCD_Vid_GOTOXY(0,0);
					LCD_Vid_Send_String("User name is not existed !!!");
					LCD_Vid_GOTOXY(0,1);
					LCD_Vid_Send_String("Remaining Attempts: ");
					LCD_Vid_Send_Num(LOC_u8_Attempts);
					LOC_u8_In = 0;
					_delay_ms(1000);
					if(LOC_u8_Attempts > 0){
						LCD_Vid_Send_Command(0x01);
						LCD_Vid_GOTOXY(0,0);
						LCD_Vid_Send_String("Enter your username:");
						LCD_Vid_GOTOXY(0,1);
					}
					LOC_u16_Check = 0x200;
				}
			}
		}
		LOC_u8_Key = 0xff;
	}
	LCD_Vid_Send_Command(0x01);
	DIO_Vid_Set_Pin_Val(PORTA,PIN1,HIGH);
	LCD_Vid_GOTOXY(0,0);
	LCD_Vid_Send_String("You have used all your attempts !!!");
	while (1);
}
/**************************************************************************************************/

void User_Mode_Control(void){
	u8 LOC_u8_Key = 0xff;
	u8 LOC_u8_KeyPad = 0xff;
	_delay_ms(2000);
	LCD_Vid_Send_Command(0x01);
	while (1)
	{
		if(GLO_u8_Flag)
		{
			LCD_Vid_GOTOXY(0,0);
			LCD_Vid_Send_String("Room Temperature ");
			LCD_Vid_Send_Num(GLO_u32_Temp);
			GLO_u8_Flag = 0;
		}
		LOC_u8_KeyPad = KEYPAD_u8_Get_Key();
		LOC_u8_Key = UART_u8_Rx_Control();
		switch(LOC_u8_Key){
			case 'A':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN3);
						break;
			case 'B':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN6);
						break;
			case 'C':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN7);
						break;
			case 'D':	DIO_Vid_Toggle_Pin_Val(PORTC,PIN6);
						break;
			case 'E':	DIO_Vid_Toggle_Pin_Val(PORTC,PIN7);
						break;
			case 'F':	if(GLO_u8_Dim_dutyCycle == 90)
						{
							UART_Vid_Tx_String("\nMAX BRIGHTNESS !!\n");
							LCD_Vid_Send_Command(0x01);
							LCD_Vid_GOTOXY(0,1);
							LCD_Vid_Send_String("MAX BRIGHTNESS !!");
						}
						else
						{
							LCD_Vid_Send_Command(0x01);
							GLO_u8_Dim_dutyCycle+=10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case 'G':	if(GLO_u8_Dim_dutyCycle == 0)
						{
							UART_Vid_Tx_String("\nMIN BRIGHTNESS !!\n");
							LCD_Vid_Send_Command(0x01);
							LCD_Vid_GOTOXY(0,1);
							LCD_Vid_Send_String("MIN BRIGHTNESS !!");
						}
						else
						{
							LCD_Vid_Send_Command(0x01);
							GLO_u8_Dim_dutyCycle-=10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case 'H':	UART_Vid_Tx_String("\nADMIN ONLY FEATURE !\n");
						break;
			case 'K':	UART_Vid_Tx_String("\nADMIN ONLY FEATURE !\n");
						break;
			case 'I':	UART_Vid_Tx_String("\nADMIN ONLY FEATURE !\n");
						break;
			case 'J':	UART_Vid_Tx_String("\nGOODBYE\n");
						LCD_Vid_Send_Command(0x01);
						LCD_Vid_GOTOXY(0,1);
						LCD_Vid_Send_String("GOODBYE");
						_delay_ms(2000);
						return;
			case 0xff:	break;
			default:	UART_Vid_Tx_String("\nWRONG INPUT\n");
						
		}
		switch(LOC_u8_KeyPad){
			case '1':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN3);
						break;
			case '2':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN6);
						break;
			case '3':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN7);
						break;
			case '4':	DIO_Vid_Toggle_Pin_Val(PORTC,PIN6);
						break;
			case '5':	DIO_Vid_Toggle_Pin_Val(PORTC,PIN7);
						break;
			case '+':	if(GLO_u8_Dim_dutyCycle == 90)
						{
							UART_Vid_Tx_String("\nMAX BRIGHTNESS !!\n");
							LCD_Vid_Send_Command(0x01);
							LCD_Vid_GOTOXY(0,1);
							LCD_Vid_Send_String("MAX BRIGHTNESS !!");
						}
						else
						{
							LCD_Vid_Send_Command(0x01);
							GLO_u8_Dim_dutyCycle+=10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case '-':	if(GLO_u8_Dim_dutyCycle == 0)
						{
							UART_Vid_Tx_String("\nMIN BRIGHTNESS !!\n");
							LCD_Vid_Send_Command(0x01);
							LCD_Vid_GOTOXY(0,1);
							LCD_Vid_Send_String("MIN BRIGHTNESS !!");
						}
						else
						{
							LCD_Vid_Send_Command(0x01);
							GLO_u8_Dim_dutyCycle-=10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case 'C':	UART_Vid_Tx_String("\nGOODBYE!\n");
						LCD_Vid_Send_Command(0x01);
						LCD_Vid_GOTOXY(0,1);
						LCD_Vid_Send_String("GOODBYE");
						_delay_ms(2000);
						return;
			case 0xff:	break;
			default:	LCD_Vid_Send_Command(0x01);
						LCD_Vid_GOTOXY(0,1);
						LCD_Vid_Send_String("WRONG INPUT !!!");
						_delay_ms(2000);
		}
	}
}
/**************************************************************************************************/
void User_Mode_Control_Keypad(void){
	u8 LOC_u8_Key = 0xff;
	u8 LOC_u8_KeyPad = 0xff;
	_delay_ms(2000);
	LCD_Vid_Send_Command(0x01);
	while(1)
	{
		if(GLO_u8_Flag)
		{
			LCD_Vid_GOTOXY(0,0);
			LCD_Vid_Send_String("Room Temperature ");
			LCD_Vid_Send_Num(GLO_u32_Temp);
			GLO_u8_Flag = 0;
		}
		LOC_u8_KeyPad = KEYPAD_u8_Get_Key();
		LOC_u8_Key = UART_u8_Rx_Control();
		if(LOC_u8_Key == '1'){
			LCD_Vid_Send_Command(0x01);
			LCD_Vid_GOTOXY(0,1);
			LCD_Vid_Send_String("Admin is online");
			Admin_Mode_Login();
			UART_Vid_Tx_String("\nOnly Admin can interrupt\n");
			LCD_Vid_Send_Command(0x01);
			LCD_Vid_GOTOXY(0,1);
			LCD_Vid_Send_String("You are back online");
			_delay_ms(1000);
			LCD_Vid_Send_Command(0x01);
		}
		else if(LOC_u8_Key != 0xff){
			UART_Vid_Tx_String("\nAnother user is controlling from Keypad\n");
			UART_Vid_Tx_String("\nOnly Admin can interrupt\n");
		}
		switch(LOC_u8_KeyPad){
			case '1':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN3);
						break;
			case '2':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN6);
						break;
			case '3':	DIO_Vid_Toggle_Pin_Val(PORTD,PIN7);
						break;
			case '4':	DIO_Vid_Toggle_Pin_Val(PORTC,PIN6);
						break;
			case '5':	DIO_Vid_Toggle_Pin_Val(PORTC,PIN7);
						break;
			case '+':	if(GLO_u8_Dim_dutyCycle == 90)
						{
							LCD_Vid_Send_Command(0x01);
							LCD_Vid_GOTOXY(0,1);
							LCD_Vid_Send_String("MAX BRIGHTNESS !!");
						}
						else
						{
							LCD_Vid_Send_Command(0x01);
							GLO_u8_Dim_dutyCycle+=10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case '-':	if(GLO_u8_Dim_dutyCycle == 0)
						{
							LCD_Vid_Send_Command(0x01);
							LCD_Vid_GOTOXY(0,1);
							LCD_Vid_Send_String("MIN BRIGHTNESS !!");
						}
						else
						{
							LCD_Vid_Send_Command(0x01);
							GLO_u8_Dim_dutyCycle-=10;
							Timer0_Vid_Fast_PWM(GLO_u8_Dim_dutyCycle);
						}
						break;
			case 'C':	LCD_Vid_Send_Command(0x01);
						LCD_Vid_GOTOXY(0,1);
						LCD_Vid_Send_String("GOODBYE");
						_delay_ms(2000);
						return;
			case 0xff:	break;
			default:	LCD_Vid_Send_Command(0x01);
						LCD_Vid_GOTOXY(0,1);
						LCD_Vid_Send_String("WRONG INPUT !!!");
						_delay_ms(2000);
		}
	}
	return;
}