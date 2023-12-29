/*
 * Timer0_interface.h
 *
 * Created: 9/23/2023 3:03:59 PM
 *  Author: mazen
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_
/* TIMER MODE*/
#define NOMRAL_MODE		0
#define PWM_MODE		1
#define CTC_MODE		2
#define FAST_PWM_MODE	3
#define TIMER0_MODE CTC_MODE

/* PRESCALER */
#define TIMER_STOPPED		0
#define No_PRESCALER		1
#define PRESCALER_8			2
#define PRESCALER_64		3
#define PRESCALER_256		4
#define PRESCALER_1024		5

/* OCR VAL */
#define OCR_VAL				250

void Timer0_Vid_Start(u8 copy_u8_prescaler);
void Timer0_Vid_Stop(void);
void Timer0_Vid_OVF_Interrupt_Enable(void);
void Timer0_Vid_Delay_ms(u32 copy_u32_Delay);
void Timer0_Vid_Delay_us(u32 copy_u32_Delay);
void Timer0_Vid_Call_Back(void (*copy_ptr_fun)(void),u8 copy_u8_mode);
void Timer0_Vid_CTC_Init(void);
void Timer0_Vid_Fast_PWM(u8 copy_u8_DutyCycle);
void Timer0_Vid_PWM_PC(u8 copy_u8_DutyCycle);

#endif /* TIMER0_INTERFACE_H_ */