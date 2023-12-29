/*
 * ADC_private.h
 *
 * Created: 9/16/2023 3:51:24 PM
 *  Author: Khaled AbdLdayem
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX_REG      *((volatile u8*) 0x27)
#define ADCSRA_REG     *((volatile u8*) 0x26)
#define ADC_REG          *((volatile u16*) 0x24)
#define SFIOR_REG          *((volatile u8*) 0x50)

#endif /* ADC_PRIVATE_H_ */
