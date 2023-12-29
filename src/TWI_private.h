/*
 * TWI_private.h
 *
 * Created: 11/15/2023 9:52:27 PM
 *  Author: mazen
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWBR_REG		*((volatile u8*)0x20)	//TWI Bit Rate Register

#define TWCR_REG		*((volatile u8*)0x56)	//TWI Control Register
#define TWINT		7							//TWI Interrupt Flag
#define TWEA		6							//TWI Enable Acknowledge Bit
#define TWSTA		5							//TWI START Condition Bit
#define TWSTO		4							//TWI STOP Condition Bit
#define TWWC		3							//TWI Write Collision Flag
#define TWEN		2							//TWI Enable Bit
#define TWIE		0							//TWI Interrupt Enable

#define TWSR_REG		*((volatile u8*)0x21)	//TWI Status Register
#define TWPS1		1							//TWI Prescaler Bit
#define TWPS0		0							//TWI Prescaler Bit

#define TWDR_REG		*((volatile u8*)0x23)	//TWI Data Register

#define TWAR_REG		*((volatile u8*)0x22)	//TWI Address Register
#define TWGCE		0							//TWI General Call Recognition Enable Bit

/* TWI STATUS */

#define START_ACK                             0x08   /* start has been send */
#define REP_START                             0x10   /* repeated start*/
#define SLAVE_ADD_AND_WR_ACK                  0x18   /*MASTER transmit (slave address +write request  */
#define SLAVE_ADD_AND_RD_ACK                  0x40  /*MASTER transmit (slave address +write request  */
#define MASTER_WR_BYTE_ACK                    0x28   /*MASTER transmit Data ack  */
#define MASTER_RD_BYTE_WITH_ACK               0x50   /*MASTER  receive data with ack  */
#define MASTER_RD_BYTE_WITH_NACK              0x58   /*MASTER  receive data with ack  */
#define SLAVE_ADD_RCVD_RD_REQ                 0xA8   /* MEANS that slave address is received with read request  */
#define SLAVE_ADD_RCVD_WD_REQ                 0x60   /* MEANS that slave address is received with Write request  */
#define SLAVE_DATA_RECEIVED                   0x80  /* MEANS that data byte is received */
#define SLAVE_BYTE_TRANSMITTIED               0xB8  /* MEANS that data byte  are transmitted  */

#endif /* I2C_PRIVATE_H_ */