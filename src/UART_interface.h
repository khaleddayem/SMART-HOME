/*
 * UART_interface.h
 *
 * Created: 10/13/2023 4:10:53 PM
 *  Author: mazen
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define MOD_10(NUM) (NUM%10)
#define DIV_BY_10(NUM) (NUM/10)
#define ASCII_OF_0	48
u8 UART_u8_Rx_Control(void);
void UART_Vid_Init(void);
void UART_Vid_Tx(u8 copy_u8_data);
u8 UART_u8_Rx(void);
void UART_Vid_Tx_String(c8* copy_c8_data);
void UART_Vid_Tx_Num(u64 copy_u64_num);

#endif /* UART_INTERFACE_H_ */