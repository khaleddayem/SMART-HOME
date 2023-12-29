/*
 * Timer1_interface.c
 *
 * Created: 9/29/2023 9:48:37 PM
 *  Author: mazen
 */ 
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Timer1_private.h"
#include "Timer1_interface.h"
#include "Vector_Num.h"


void (*ICU_CB_ptr)(void) = 0;

void Timer1_Vid_Start(u8 copy_u8_prescaler){
	TCCR1B_REG &= 0b11111000;
	TCCR1B_REG |= copy_u8_prescaler;
}
void Timer1_Vid_Reset(void){
	TCNT1_REG = 0x0000;
}

void Timer1_Vid_Fast_PWM_8_bit(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB){
	if(copy_u8_ORCA == 1)
		DIO_Vid_Set_Pin_Dir(PORTD,PIN5,OUTPUT);
	if(copy_u8_ORCB == 1)
		DIO_Vid_Set_Pin_Dir(PORTD,PIN4,OUTPUT);
	/* select prescaler */
	Timer1_Vid_Start(No_PRESCALER);
	/* Fast PWM MODE */
	SET_BIT(TCCR1A_REG,WGM10);
	CLR_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	CLR_BIT(TCCR1B_REG,WGM13);
	if(copy_u8_ORCA == 1){
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1A1);
		CLR_BIT(TCCR1A_REG,COM1A0);
		/* OCR equation */
		OCR1A_REG = (copy_u8_DutyCycle*2.56);
		while (GET_BIT(TIFR_REG,OCF1A)==0); // polling OCF0 flag
		SET_BIT(TIFR_REG,OCF1A); // clr flag
	}else{}
		
	if(copy_u8_ORCB == 1){
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1B1);
		CLR_BIT(TCCR1A_REG,COM1B0);
		/* OCR equation */
		OCR1B_REG = (copy_u8_DutyCycle*2.56);
		while (GET_BIT(TIFR_REG,OCF1B)==0); // polling OCF0 flag
		SET_BIT(TIFR_REG,OCF1B); // clr flag
	}else{}
}
void Timer1_Vid_Fast_PWM_9_bit(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB){
	if(copy_u8_ORCA == 1)
		DIO_Vid_Set_Pin_Dir(PORTD,PIN5,OUTPUT);
	if(copy_u8_ORCB == 1)
		DIO_Vid_Set_Pin_Dir(PORTD,PIN4,OUTPUT);
	/* select prescaler */
	Timer1_Vid_Start(No_PRESCALER);
	/* Fast PWM MODE */
	CLR_BIT(TCCR1A_REG,WGM10);
	SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	CLR_BIT(TCCR1B_REG,WGM13);
	if(copy_u8_ORCA == 1){
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1A1);
		CLR_BIT(TCCR1A_REG,COM1A0);
		/* OCR equation */
		OCR1A_REG = (copy_u8_DutyCycle*5.12);
		while (GET_BIT(TIFR_REG,OCF1A)==0); // polling OCF0 flag
		SET_BIT(TIFR_REG,OCF1A); // clr flag
	}else{}
	if(copy_u8_ORCB == 1){
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1B1);
		CLR_BIT(TCCR1A_REG,COM1B0);
		/* OCR equation */
		OCR1B_REG = (copy_u8_DutyCycle*5.12);
		while (GET_BIT(TIFR_REG,OCF1B)==0); // polling OCF0 flag
		SET_BIT(TIFR_REG,OCF1B); // clr flag
	}else{}
}
void Timer1_Vid_Fast_PWM_10_bit(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB){
	/* select prescaler */
	Timer1_Vid_Start(No_PRESCALER);
	/* Fast PWM MODE */
	SET_BIT(TCCR1A_REG,WGM10);
	SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	CLR_BIT(TCCR1B_REG,WGM13);
	if(copy_u8_ORCA == 1){
		DIO_Vid_Set_Pin_Dir(PORTD,PIN5,OUTPUT);
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1A1);
		CLR_BIT(TCCR1A_REG,COM1A0);
		/* OCR equation */
		OCR1A_REG = (copy_u8_DutyCycle*10.24);
		while (GET_BIT(TIFR_REG,OCF1A)==0); // polling OCF0 flag
		SET_BIT(TIFR_REG,OCF1A); // clr flag
	}else{}
	if(copy_u8_ORCB == 1){
		DIO_Vid_Set_Pin_Dir(PORTD,PIN4,OUTPUT);
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1B1);
		CLR_BIT(TCCR1A_REG,COM1B0);
		/* OCR equation */
		OCR1B_REG = (copy_u8_DutyCycle*10.24);
		while (GET_BIT(TIFR_REG,OCF1B)==0); // polling OCF0 flag
		SET_BIT(TIFR_REG,OCF1B); // clr flag
	}else{}
}

void Timer1_Vid_Fast_PWM_ICR1(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB){
	/* select prescaler */
	Timer1_Vid_Start(PRESCALER_8);
	/* Fast PWM MODE ICR */
	CLR_BIT(TCCR1A_REG,WGM10);
	SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	SET_BIT(TCCR1B_REG,WGM13);
	/* OC1A */
	if(copy_u8_ORCA == 1){
		DIO_Vid_Set_Pin_Dir(PORTD,PIN5,OUTPUT);
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1A1);
		CLR_BIT(TCCR1A_REG,COM1A0);
		/* OCR equation */
		ICR1_REG = 40000;
		OCR1A_REG = (copy_u8_DutyCycle*400);
		//while (GET_BIT(TIFR_REG,ICF1)==0); // polling OCF0 flag
		//SET_BIT(TIFR_REG,ICF1); // clr flag
	}else{}
	/* OC1B */
	if(copy_u8_ORCB == 1){
		DIO_Vid_Set_Pin_Dir(PORTD,PIN4,OUTPUT);
		/* non-inverting mode */
		SET_BIT(TCCR1A_REG,COM1B1);
		CLR_BIT(TCCR1A_REG,COM1B0);
		/* OCR equation */
		ICR1_REG = 40000;
		OCR1B_REG = (copy_u8_DutyCycle*400);
		//while (GET_BIT(TIFR_REG,ICF1)==0); // polling OCF0 flag
		//SET_BIT(TIFR_REG,ICF1); // clr flag
	}else{}
}

void Timer1_Vid_Fast_PWM_ICR(void){
	/* non-inverting mode */
	SET_BIT(TCCR1A_REG,COM1A1);
	CLR_BIT(TCCR1A_REG,COM1A0);
	/* Fast PWM MODE ICR */
	CLR_BIT(TCCR1A_REG,WGM10);
	SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	SET_BIT(TCCR1B_REG,WGM13);
	/* SET ICR VAL */
	ICR1_REG = 40000;
	//OCR1A_REG = 2000;
	/* select prescaler */
	Timer1_Vid_Start(PRESCALER_8);
}


void Timer1_Vid_Set_Compare_Val(u16 copy_u16_angle){
	OCR1A_REG = ((copy_u16_angle/180.0) * ICR1_REG * (0.125-0.025))+ICR1_REG*0.025 ;
}
void Timer1_Vid_Normal_Mode_Init(void){
	
	Timer1_Vid_Start(PRESCALER_1024);
}

void ICU_Vid_Sense_Control(u8 Sense_Control){
	/* Sense Control */
	if(Sense_Control == FALLING_EDGE){
		CLR_BIT(TCCR1B_REG,ICES1);
	}
	if(Sense_Control == RISING_EDGE){
		SET_BIT(TCCR1B_REG,ICES1);
	}
	/* ENABLE GLOBAL INTERRUPT (GIE)*/
	GIE_Vid_Enable();
	/* ENABLE ICU INTERRUPT (TICIE1)*/
	SET_BIT(TIMSK_REG,TICIE1);
}
void TIM1_Vid_FastPWM_Mode14(u16 copy_u16_ICR1,f32 copy_f32_dutycycle)
{
	/* Choose Fast PWM mode with ICR1 top value */
	CLR_BIT(TCCR1A_REG,0);
	SET_BIT(TCCR1A_REG,1);
	SET_BIT(TCCR1B_REG,3);
	SET_BIT(TCCR1B_REG,4);
	/* Non inverting mode */
	SET_BIT(TCCR1A_REG,5);
	SET_BIT(TCCR1A_REG,7);
	CLR_BIT(TCCR1A_REG,4);
	CLR_BIT(TCCR1A_REG,6);
	
	/* Set top value */
	ICR1_REG = copy_u16_ICR1;
	
	/* Set duty cycle */
	OCR1A_REG = copy_f32_dutycycle*(copy_u16_ICR1/100);
	OCR1B_REG = copy_f32_dutycycle*(copy_u16_ICR1/100);
	
	/* Clear the First 3 bits */
	TCCR1B_REG &= 0b11111000;
	/* Set the pre scaler */
	TCCR1B_REG |= PRESCALER_256;
	
	while(GET_BIT(TIFR_REG,4)==0);
	SET_BIT(TIFR_REG,4);
}

u16  ICU_u16_Read_ICR_Val(void){
	
	return ICR1_REG;
	
}
void ICU_Vid_CALLBACK_FN(void (*copy_ptr_fun)(void)){
	
	ICU_CB_ptr = copy_ptr_fun;
	
}
ISR(TIMER1_CAPT){
	
	ICU_CB_ptr();
	
}