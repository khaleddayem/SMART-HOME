/*
 * KEYPAD_interface.h
 *
 * Created: 9/8/2023 5:00:07 PM
 *  Author: mazen
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
/*****************************************************************************
* Function Name: KEYPAD_Vid_Init
* Purpose      : Initialize Keypad
* Parameters   : void
* Return value : void
*****************************************************************************/
void KEYPAD_Vid_Init(void);
/*****************************************************************************
* Function Name: KEYPAD_u8_Get_Key
* Purpose      : GET Key from Keypad
* Parameters   : void
* Return value : u8
*****************************************************************************/
u8 KEYPAD_u8_Get_Key();



#endif /* KEYPAD_INTERFACE_H_ */