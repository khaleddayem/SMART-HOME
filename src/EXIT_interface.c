/*
 * EXIT_interface.c
 *
 * Created: 09/09/2023 16:21:35
 *  Author: AMIT
 */ 
#include "BIT_MATH.h" 
#include "STD_TYPE.h" 
#include "EXIT_interface.h"
#include "EXIT_private.h" 
#include "GIE_interface.h"  
#include "DIO_interface.h"
#include "Vector_Num.h"

void (*ptr_0)(void);
void (*ptr_1)(void);
void (*ptr_2)(void);
u8 LOC_u8_Toggle;
/*	INITIALIZE according to SENSE control	*/
void EXT_Vid_Interrupt_Init() {
	
	#if SENSE_CONTROL == LOW_LEVEL
		/* INT0 */
		CLR_BIT(MCUCR_REG,ISC01) ;
		CLR_BIT(MCUCR_REG,ISC00) ;
	    /* INT1 */
	    CLR_BIT(MCUCR_REG,ISC11) ; 
		CLR_BIT(MCUCR_REG,ISC10) ;
		
    #elif SENSE_CONTROL == ANY_LOGIC_CHANGE
		/* INT0 */
		CLR_BIT(MCUCR_REG,ISC01) ;
		SET_BIT(MCUCR_REG,ISC00) ;
	    /* INT1 */
	    CLR_BIT(MCUCR_REG,ISC11) ;
	    SET_BIT(MCUCR_REG,ISC10) ;
		
	#elif SENSE_CONTROL == FALLING_EDGE
		/* INT0*/
		SET_BIT(MCUCR_REG,ISC01) ;
		CLR_BIT(MCUCR_REG,ISC00) ;
		/* INT1 */
		SET_BIT(MCUCR_REG,ISC11) ;
		CLR_BIT(MCUCR_REG,ISC10) ;
		/* INT2 */
		CLR_BIT(MCUCSR_REG,ISC2)  ;
		
	#elif SENSE_CONTROL==RISING_EDGE
		/* INT0 */
		SET_BIT(MCUCR_REG,ISC01) ;
		SET_BIT(MCUCR_REG,ISC00) ;
	    /* INT1 */
	    SET_BIT(MCUCR_REG,ISC11) ;
	    SET_BIT(MCUCR_REG,ISC10) ;
	    /* INT2 */
	    SET_BIT(MCUCSR_REG,ISC2)  ;
		
	 #endif
}

void EXT_Vid_Interrupt0(){
	
	/* enable global interrupt (GIE) */
	GIE_Vid_Enable(); 
	/* enable INT0 */
	SET_BIT(GICR_REG,INT_0) ; 
	
}
void EXT_Vid_Interrupt1(){
	
	/* enable global interrupt (GIE) */
	GIE_Vid_Enable();
	/* enable INT0 */
	SET_BIT(GICR_REG,INT_1) ;
	
}
void EXT_Vid_Interrupt2(){
	
	/* enable global interrupt (GIE) */
	GIE_Vid_Enable();
	/* enable INT0 */
	SET_BIT(GICR_REG,INT_2) ;
	
}

void SET_Vid_Call_Back(void(*pointer_fun)(void),u8 copy_u8_INT){
	if(copy_u8_INT == INT0)
		ptr_0 = pointer_fun;
	else if(copy_u8_INT == INT1)
		ptr_1 = pointer_fun;
	else if(copy_u8_INT == INT2)
		ptr_2 = pointer_fun;
}

/* ISR */
ISR(_INT_0){
	ptr_0();
}

ISR(_INT_1){
	ptr_1();	
}

ISR(_INT_2){
	ptr_2();	
}

