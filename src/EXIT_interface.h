/*
 * EXIT_interface.h
 *
 * Created: 09/09/2023 16:22:14
 *  Author: AMIT
 */ 


#ifndef EXIT_INTERFACE_H_
#define EXIT_INTERFACE_H_

/* SENSE control  */

#define  SENSE_CONTROL    RISING_EDGE

#define  RISING_EDGE      0
#define  FALLING_EDGE     1
#define  ANY_LOGIC_CHANGE 2 
#define  LOW_LEVEL        3 

#define INT0	0
#define INT1	1 
#define INT2	2	
/*****************************************************************************
* Function Name: EXT_Vid_Interrupt_Init
* Purpose      : Initialize INT
* Parameters   : void
* Return value : void
*****************************************************************************/
void EXT_Vid_Interrupt_Init() ; 
/*****************************************************************************
* Function Name: EXT_Vid_Interrupt0
* Purpose      : Enable INT0 ( SET --> HIGH )
* Parameters   : void
* Return value : void
*****************************************************************************/
void EXT_Vid_Interrupt0() ; 
/*****************************************************************************
* Function Name: EXT_Vid_Interrupt1
* Purpose      : Enable INT1 ( SET --> HIGH )
* Parameters   : void
* Return value : void
*****************************************************************************/
void EXT_Vid_Interrupt1();
/*****************************************************************************
* Function Name: EXT_Vid_Interrupt2
* Purpose      : Enable INT2 ( SET --> HIGH )
* Parameters   : void
* Return value : void
*****************************************************************************/
void EXT_Vid_Interrupt2();

void SET_Vid_Call_Back(void(*pointer_fun)(void),u8 copy_u8_INT);

#endif /* EXIT_INTERFACE_H_ */