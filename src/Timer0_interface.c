/*
 * Timer0_interface.c
 *
 * Created: 9/23/2023 3:04:28 PM
 *  Author: mazen
 */ 
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "Timer0_interface.h"
#include "Timer0_private.h"
#include "Vector_Num.h"

void (*OVF_CB_ptr)(void)=null; 
void (*CTC_CB_ptr)(void)=null; 

//u8 LOC_u8_Sec = 0;
//u16 LOC_u16_Count=0;
void Timer0_Vid_Start(u8 copy_u8_prescaler){
	
	/*#if TIMER0_MODE == NOMRAL_MODE
	CLR_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
	#elif TIMER0_MODE == PWM_MODE
	SET_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
	#elif TIMER0_MODE == CTC_MODE
	CLR_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	#elif TIMER0_MODE == FAST_PWM_MODE
	SET_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	#endif*/
	
	TCCR0_REG &= 0b11111000;
	TCCR0_REG |= copy_u8_prescaler;
}

void Timer0_Vid_Stop(void){
	
	TCCR0_REG = TIMER_STOPPED;
	
}

void Timer0_Vid_OVF_Interrupt_Enable(void){
	CLR_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
	/* ENABLE GLOBAL INTERRUPT (GIE)*/
	GIE_Vid_Enable();
	/* ENABLE TIMER0 INTERRUPT (TOIE)*/
	SET_BIT(TIMSK_REG,TOIE0);
}

void Timer0_Vid_Delay_ms(u32 copy_u32_Delay){
	u32 LOC_u32_Count= 0;
	Timer0_Vid_Start(PRESCALER_64);
	copy_u32_Delay = copy_u32_Delay/1.024;
	while(LOC_u32_Count<copy_u32_Delay){
		LOC_u32_Count++;
		while (GET_BIT(TIFR_REG,TOV0)==0); // polling OVF flag
		SET_BIT(TIFR_REG,TOV0); // clr flag
	}
	Timer0_Vid_Stop();
}

void Timer0_Vid_Delay_us(u32 copy_u32_Delay){
	u64 LOC_u64_Count= 0;
	Timer0_Vid_Start(No_PRESCALER);
	copy_u32_Delay = copy_u32_Delay/16;
	while(LOC_u64_Count<copy_u32_Delay){
		LOC_u64_Count++;
		while (GET_BIT(TIFR_REG,TOV0)==0); // polling OVF flag
		SET_BIT(TIFR_REG,TOV0); // clr flag
	}
	Timer0_Vid_Stop();
}

void Timer0_Vid_CTC_Init(){
	CLR_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	OCR0_REG = OCR_VAL;
	/* ENABLE GLOBAL INTERRUPT (GIE)*/
	GIE_Vid_Enable();
	/* ENABLE TIMER0 INTERRUPT (OCIE0)*/
	SET_BIT(TIMSK_REG,OCIE0);
	//Timer0_Vid_Start(PRESCALER_64);
}

void Timer0_Vid_Fast_PWM(u8 copy_u8_DutyCycle){
	DIO_Vid_Set_Pin_Dir(PORTB,PIN3,OUTPUT);
	/* select prescaler */
	Timer0_Vid_Start(PRESCALER_64);
	/* Fast PWM MODE */
	SET_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	/* non-inverting mode */
	CLR_BIT(TCCR0_REG,COM00);
	SET_BIT(TCCR0_REG,COM01);
	/* OCR equation */
	OCR0_REG = copy_u8_DutyCycle*2.56;

	while (GET_BIT(TIFR_REG,OCF0)==0); // polling OCF0 flag
	SET_BIT(TIFR_REG,OCF0); // clr flag
}

void Timer0_Vid_PWM_PC(u8 copy_u8_DutyCycle){
	DIO_Vid_Set_Pin_Dir(PORTB,PIN3,OUTPUT);
	/* select prescaler */
	Timer0_Vid_Start(PRESCALER_64);
	/* PWM MODE */
	SET_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
	/* inverting mode */
	SET_BIT(TCCR0_REG,COM00);
	SET_BIT(TCCR0_REG,COM01);
	/* OCR equation */
	OCR0_REG = copy_u8_DutyCycle*2.56;
	
	while (GET_BIT(TIFR_REG,OCF0)==0); // polling OCF0 flag
	SET_BIT(TIFR_REG,OCF0); // clr flag
}

void Timer0_Vid_Call_Back(void (*copy_ptr_fun)(void),u8 copy_u8_mode){
	if (copy_u8_mode == NOMRAL_MODE)
		OVF_CB_ptr = copy_ptr_fun;
	//if (copy_u8_mode == PWM_MODE)
	
	if (copy_u8_mode == CTC_MODE)
		CTC_CB_ptr = copy_ptr_fun;
	//if (copy_u8_mode == FAST_PWM_MODE)
	

}

ISR(TIMER0_OVF){
	
	OVF_CB_ptr();
	
}

ISR(TIMER0_COMP){
	
	CTC_CB_ptr();
	
}