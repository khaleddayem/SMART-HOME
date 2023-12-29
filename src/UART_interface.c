/*
 * UART_interface.c
 *
 * Created: 10/13/2023 4:10:42 PM
 *  Author: mazen
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "UART_private.h"
#include "UART_interface.h"
#define F_CPU 16000000
#include "util/delay.h"

void UART_Vid_Init(void){
	/* Async Mode */
	//CLR_BIT(UCSRC_REG,UMSEL);
	UCSRC_REG = 0b10000110; // (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0)
	/* SET baud rate*/
	UBRRL_REG = 103; // F = 16MHZ, 9600 (bps)
	/* enable TX */
	SET_BIT(UCSRB_REG,TXEN);
	/* enable RX */
	SET_BIT(UCSRB_REG,RXEN);
}
void UART_Vid_Tx(u8 copy_u8_data){
	while(GET_BIT(UCSRA_REG,UDRE) == 0); // waiting to send data
	UDR_REG = copy_u8_data;
}
u8 UART_u8_Rx(void){
	while(GET_BIT(UCSRA_REG,RXC) == 0);
	return UDR_REG;
}
u8 UART_u8_Rx_Control(void){
	u8 LOC_u8_data = 0;
	while(GET_BIT(UCSRA_REG,RXC) == 0 && LOC_u8_data < 10){ // waiting to receive data
		LOC_u8_data++;
		_delay_ms(5);
		if(LOC_u8_data == 9){
			return 0xff;
		}
	}
	return UDR_REG;
}


void UART_Vid_Tx_String(c8* copy_c8_data){
	u8 LOC_u8_Counter = 0;
	while(copy_c8_data[LOC_u8_Counter] != '\0'){
		UART_Vid_Tx(copy_c8_data[LOC_u8_Counter]);
		LOC_u8_Counter++;
	}
}

void UART_Vid_Tx_Num(u64 copy_u64_num){
	s8 LOC_u8_In = 0;
	u8 LOC_u8_Count = 0;
	u8 LOC_u8_All_Digits[10]={ASCII_OF_0};
	while(copy_u64_num>0){
		LOC_u8_All_Digits[LOC_u8_Count] = MOD_10(copy_u64_num) + ASCII_OF_0;
		copy_u64_num = DIV_BY_10(copy_u64_num);
		LOC_u8_Count++;
	}
	if(LOC_u8_Count == 0){
		LOC_u8_Count++;
	}
	for(LOC_u8_In = (LOC_u8_Count-1); LOC_u8_In >= 0; LOC_u8_In--){
		UART_Vid_Tx(LOC_u8_All_Digits[LOC_u8_In]);
	}
}