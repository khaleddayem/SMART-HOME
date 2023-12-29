/*
 * UART_private.h
 *
 * Created: 10/13/2023 4:10:22 PM
 *  Author: mazen
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR_REG *((volatile u8*)0x2C)
#define UCSRA_REG *((volatile u8*)0x2B)
#define RXC		7
#define UDRE	5
#define U2X		1
#define UCSRB_REG *((volatile u8*)0x2A)
#define RXEN	4
#define TXEN	3
#define UCSRC_REG *((volatile u8*)0x40)
#define URSEL	7
#define UMSEL	6
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UBRRL_REG *((volatile u8*)0x29)

#endif /* UART_PRIVATE_H_ */