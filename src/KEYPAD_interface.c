/*
 * KEYPAD_interface.c
 *
 * Created: 9/8/2023 4:59:57 PM
 *  Author: mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"

u8 GLO_u8_DataARRAY[4][4]={	{'7','8','9','/'},
							{'4','5','6','*'},
							{'1','2','3','-'},
							{'C','0','=','+'}};

void KEYPAD_Vid_Init(void){
	u8 LOC_u8_ROWARRAY[4]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN};
	u8 LOC_u8_COLARRAY[4]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN};
	u8 LOC_u8_IN = 0;
	for(LOC_u8_IN = 0; LOC_u8_IN < 4; LOC_u8_IN++){
		/* MAKE ROW PINS --> INPUT */
		DIO_Vid_Set_Pin_Dir(KEYPAD_ROW_PORT,LOC_u8_ROWARRAY[LOC_u8_IN],INPUT);
		/* ACTIVE PULL UP RESISTOR */
		DIO_Vid_Set_Pin_Val(KEYPAD_ROW_PORT,LOC_u8_ROWARRAY[LOC_u8_IN],HIGH);
	}
	for(LOC_u8_IN = 0; LOC_u8_IN < 4; LOC_u8_IN++){
		/* MAKE COL PINS --> OUTPUT */
		DIO_Vid_Set_Pin_Dir(KEYPAD_COL_PORT,LOC_u8_COLARRAY[LOC_u8_IN],OUTPUT);
		/* ACTIVE PULL UP RESISTOR */
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,LOC_u8_COLARRAY[LOC_u8_IN],HIGH);
	}
}

u8 KEYPAD_u8_Get_Key(){
	u8 LOC_u8_ROWARRAY[4]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN};
	u8 LOC_u8_COLARRAY[4]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN};
	u8  LOC_u8_ROW = 0;
	u8  LOC_u8_COL = 0;
	u8  LOC_u8_KEY = 0xff;
	for(LOC_u8_COL = 0 ; LOC_u8_COL < 4; LOC_u8_COL++){
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,LOC_u8_COLARRAY[LOC_u8_COL],LOW);
		for(LOC_u8_ROW = 0 ; LOC_u8_ROW < 4; LOC_u8_ROW++){
			if(DIO_u8_Get_Pin_Val(KEYPAD_ROW_PORT,LOC_u8_ROWARRAY[LOC_u8_ROW])==0){
				LOC_u8_KEY = GLO_u8_DataARRAY[LOC_u8_ROW][LOC_u8_COL];
				while(DIO_u8_Get_Pin_Val(KEYPAD_ROW_PORT,LOC_u8_ROWARRAY[LOC_u8_ROW])==0);
				return LOC_u8_KEY ;
			}
		}
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,LOC_u8_COLARRAY[LOC_u8_COL],HIGH);
	}
	return LOC_u8_KEY ;
}
