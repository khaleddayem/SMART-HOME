/*
 * DIO_interface.c
 *
 * Created: 8/26/2023 4:19:36 PM
 *  Author: mazen
 */ 

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_interface.h"

void DIO_Vid_Set_Pin_Dir(u8 Copy_u8_port,u8 Copy_u8_pin,u8 Copy_u8_dir){
	
	if(Copy_u8_dir == OUTPUT || Copy_u8_dir == INPUT){	
		if(Copy_u8_dir == OUTPUT){
			switch(Copy_u8_port){
				/* SET DIR ---> OUTPUT */
				case PORTA: SET_BIT(DDRA_REG,Copy_u8_pin);break;
				case PORTB: SET_BIT(DDRB_REG,Copy_u8_pin);break;
				case PORTC: SET_BIT(DDRC_REG,Copy_u8_pin);break;
				case PORTD: SET_BIT(DDRD_REG,Copy_u8_pin);break;
			}
		}
		else{
			switch(Copy_u8_port){
				/* SET DIR ---> INPUT */
				case PORTA: CLR_BIT(DDRA_REG,Copy_u8_pin);break;
				case PORTB: CLR_BIT(DDRB_REG,Copy_u8_pin);break;
				case PORTC: CLR_BIT(DDRC_REG,Copy_u8_pin);break;
				case PORTD: CLR_BIT(DDRD_REG,Copy_u8_pin);break;
			}
		}
	}
}

void DIO_Vid_Set_Pin_Val(u8 Copy_u8_port,u8 Copy_u8_pin,u8 Copy_u8_val){
	
	if(Copy_u8_val == HIGH || Copy_u8_val == LOW){
		if(Copy_u8_val == HIGH){
			switch(Copy_u8_port){
				/* SET VAL ---> HIGH */
				case PORTA: SET_BIT(PORTA_REG,Copy_u8_pin);break;
				case PORTB: SET_BIT(PORTB_REG,Copy_u8_pin);break;
				case PORTC: SET_BIT(PORTC_REG,Copy_u8_pin);break;
				case PORTD: SET_BIT(PORTD_REG,Copy_u8_pin);break;
			}
		}
		else{
			switch(Copy_u8_port){
				/* SET VAL ---> LOW */
				case PORTA: CLR_BIT(PORTA_REG,Copy_u8_pin);break;
				case PORTB: CLR_BIT(PORTB_REG,Copy_u8_pin);break;
				case PORTC: CLR_BIT(PORTC_REG,Copy_u8_pin);break;
				case PORTD: CLR_BIT(PORTD_REG,Copy_u8_pin);break;
			}
		}
	}
}

u8	 DIO_u8_Get_Pin_Val(u8 Copy_u8_port,u8 Copy_u8_pin){
	
	u8 LOC_u8_Val = 0;
	
	switch(Copy_u8_port){
		/* GET VAL */
		case PORTA: LOC_u8_Val = GET_BIT(PINA_REG,Copy_u8_pin);break;
		case PORTB: LOC_u8_Val = GET_BIT(PINB_REG,Copy_u8_pin);break;
		case PORTC: LOC_u8_Val = GET_BIT(PINC_REG,Copy_u8_pin);break;
		case PORTD: LOC_u8_Val = GET_BIT(PIND_REG,Copy_u8_pin);break;
	}
	
	return LOC_u8_Val;
}

void DIO_Vid_Toggle_Pin_Val(u8 Copy_u8_port,u8 Copy_u8_pin){
	
	if(Copy_u8_pin >= PIN0 || Copy_u8_pin <= PIN7){
		switch(Copy_u8_port){
			/* TOGGLE PIN */
			case PORTA: TOGGLE_BIT(PORTA_REG,Copy_u8_pin);break;
			case PORTB: TOGGLE_BIT(PORTB_REG,Copy_u8_pin);break;
			case PORTC: TOGGLE_BIT(PORTC_REG,Copy_u8_pin);break;
			case PORTD: TOGGLE_BIT(PORTD_REG,Copy_u8_pin);break;
		}
	}
}

void DIO_Vid_Set_Port_Dir(u8 Copy_u8_port,u8 Copy_u8_dir){
	switch(Copy_u8_port){
		/* SET PORT DIR OUTPUT */
		case PORTA: DDRA_REG = Copy_u8_dir;break;
		case PORTB: DDRB_REG = Copy_u8_dir;break;
		case PORTC: DDRC_REG = Copy_u8_dir;break;
		case PORTD: DDRD_REG = Copy_u8_dir;break;
	}
}
void DIO_Vid_Set_Port_Val(u8 Copy_u8_port,u8 Copy_u8_val){
	switch(Copy_u8_port){
		/* SET PORT VAL OUTPUT */
		case PORTA: PORTA_REG = Copy_u8_val;break;
		case PORTB: PORTB_REG = Copy_u8_val;break;
		case PORTC: PORTC_REG = Copy_u8_val;break;
		case PORTD: PORTD_REG = Copy_u8_val;break;
		}
}
