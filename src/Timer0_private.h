/*
 * Timer0_private.h
 *
 * Created: 9/23/2023 3:00:05 PM
 *  Author: mazen
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define null			0
#define TCCR0_REG	*((volatile u8*)0x53)
#define WGM00	6
#define WGM01	3
#define CS00	0
#define CS01	1
#define CS02	2
#define COM00	4
#define COM01	5
#define TCNT0_REG	*((volatile u8*)0x52)
#define OCR0_REG	*((volatile u8*)0x5C)
#define TIMSK_REG	*((volatile u8*)0x59)
#define TOIE0	0
#define OCIE0	1
#define TIFR_REG	*((volatile u8*)0x58)
#define TOV0	0
#define OCF0	1

#endif /* TIMER0_PRIVATE_H_ */