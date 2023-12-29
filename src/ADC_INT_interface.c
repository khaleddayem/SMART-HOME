/*
 * ADC_interface.c
 *
 * Created: 9/16/2023 3:51:52 PM
 *  Author: Khaled AbdLdayem
 */ 
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "GIE_interface.h"
#include "Vector_Num.h"
#include "ADC_INT_interface.h"
#include "ADC_INT_private.h"

void (*ADC_INT_ISR)(void);
void ADC_Vid_Init(void)
{
	// Set ADC reference voltage to AVCC
	    ADMUX_REG |= (1 << REFS0);
	    // Set ADC channel to 0
	    ADMUX_REG &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3);
	    // Set ADC prescaler to 128 (ADC clock frequency = CPU frequency / 128)
	    ADCSRA_REG |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	    // Enable ADC
	    ADCSRA_REG |= (1 << ADEN);
	    // Enable ADC auto-triggering and select free running mode
	    ADCSRA_REG |= (1 << ADATE);
	    // Enable ADC interrupt
	    ADCSRA_REG |= (1 << ADIE);
	    // Start the first conversion
	    ADCSRA_REG |= (1 << ADSC);

	    SFIOR_REG &= ~(1 << ADTS0) & ~(1 << ADTS1) & ~(1 << ADTS2);
	    // Enable global interrupts
	    GIE_Vid_Enable();
}
void ADC_Vid_Start(void)
{
	ADCSRA_REG |= (1 << ADSC);
}
u16 ADC_READ(void)
{
	return ADC_REG;
}
/******************************************************************************************/
void ADC_Vid_Int_Enable(void)
{
	GIE_Vid_Enable();
	SET_BIT(ADCSRA_REG,ADIE);
}
/********************************************************************************************************/
void ADC_Vid_Int_Disable(void)
{
	GIE_Vid_Enable();
	CLR_BIT(ADCSRA_REG,ADIE);
}
/********************************************************************************************************/
void ADC_Vid_Int_Setcallback(void(*Fun1)(void))
{
	ADC_INT_ISR = Fun1;
}
/********************************************************************************************************/
ISR(ADC_){
	ADC_INT_ISR();
}
