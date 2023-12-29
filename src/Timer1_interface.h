/*
 * Timer1_interface.h
 *
 * Created: 9/29/2023 9:48:46 PM
 *  Author: mazen
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_
#define NORMAL_MODE			0
#define PWM_8_bit			1
#define PWM_9_bit			2
#define PWM_10_bit			3
#define CTC_MODE_OCR1A		4
#define Fast_PWM_8_bit		5
#define Fast_PWM_9_bit		6
#define Fast_PWM_10_bit		7
#define PWM_PFC_ICR1		8
#define PWM_PFC_OCR1A		9
#define PWM_ICR1			10
#define PWM_OCR1A			11
#define CTC_MODE_ICR1		12
#define Fast_PWM_ICR1		14
#define Fast_PWM_OCR1A		15

#define TIMER_STOPPED		0
#define No_PRESCALER		1
#define PRESCALER_8			2
#define PRESCALER_64		3
#define PRESCALER_256		4
#define PRESCALER_1024		5

#define  RISING_EDGE      0
#define  FALLING_EDGE     1

void ICU_Vid_Sense_Control(u8 Sense_Control);
u16  ICU_u16_Read_ICR_Val(void);
void ICU_Vid_CALLBACK_FN(void (*copy_ptr_fun)(void));
void Timer1_Vid_Fast_PWM_8_bit(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB);
void Timer1_Vid_Fast_PWM_9_bit(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB);
void Timer1_Vid_Fast_PWM_10_bit(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB);
void Timer1_Vid_Fast_PWM_ICR1(u8 copy_u8_DutyCycle,u8 copy_u8_ORCA,u8 copy_u8_ORCB);
void Timer1_Vid_Fast_PWM_ICR(void);
void Timer1_Vid_Set_Compare_Val(u16 copy_u16_angle);
void TIM1_Vid_FastPWM_Mode14(u16 copy_u16_ICR1,f32 copy_f32_dutycycle);
void Timer1_Vid_Start(u8 copy_u8_prescaler);
void Timer1_Vid_Reset(void);
void Timer1_Vid_Normal_Mode_Init(void);

#endif /* TIMER1_INTERFACE_H_ */