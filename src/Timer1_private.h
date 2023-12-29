/*
 * Timer1_private.h
 *
 * Created: 9/29/2023 9:48:58 PM
 *  Author: mazen
 */ 


#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define TCCR1A_REG  *(( volatile u8*)0x4F)
#define COM1A1	7
#define COM1A0	6
#define COM1B1	5
#define COM1B0	4
#define FOC1A	3
#define FOC1B	2
#define WGM11	1
#define WGM10	0

#define TCCR1B_REG  *(( volatile u8*)0x4E)
#define ICNC1	7
#define ICES1	6
#define WGM13	4
#define WGM12	3

#define TCNT1_REG	*(( volatile u16*)0x4C)	//TCNT1L + TCNT1H
#define OCR1A_REG	*(( volatile u16*)0x4A)	//OCR1AL + OCR1AH
#define OCR1B_REG	*(( volatile u16*)0x48)	//OCR1BL + OCR1BH
#define ICR1_REG	*(( volatile u16*)0x46)	//ICR1L  + ICR1H
#define TIMSK_REG	*((volatile u8*)0x59)
#define	TICIE1		5
#define	OCIE1A		4
#define	OCIE1B		3
#define	TOIE1		2
#define TIFR_REG	*((volatile u8*)0x58)
#define	ICF1		5
#define	OCF1A		4
#define	OCF1B		3
#define	TOV1		2

#endif /* TIMER1_PRIVATE_H_ */