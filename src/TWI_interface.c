/*
 * TWI_interface.c
 *
 * Created: 11/15/2023 9:59:02 PM
 *  Author: mazen
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "TWI_private.h"
#include "TWI_interface.h"


void TWI_Vid_Master_Init(u8 copy_u8_address){
	/* SCL Freq = 400KHz, Fs = 16MHz */
	/* SET Bit rate = 12 */
	TWBR_REG = 12;
	/* Prescale = 1 */
	CLR_BIT(TWSR_REG,TWPS0);
	CLR_BIT(TWSR_REG,TWPS1);
	if (copy_u8_address != 0)
	{
		TWAR_REG = copy_u8_address<<1;
	}
	else
	{
		/* Do nothing */
	}
	/* Enable ACK */
	SET_BIT(TWCR_REG,TWEA);
	/* Enable TWI */
	SET_BIT(TWCR_REG,TWEN);
}
void TWI_Vid_Slave_Init(u8 copy_u8_address){
	
	TWAR_REG = copy_u8_address<<1;
	/* Enable ACK */
	SET_BIT(TWCR_REG,TWEA);
	/* Enable TWI */
	SET_BIT(TWCR_REG,TWEN);
}
TWI_ErrStatus TWI_Send_Start_Condition(){
	
	/* CLR Interrupt Flag, SET Start Condition Bit */
	TWCR_REG = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	
	if ((TWSR_REG & 0xf8) != START_ACK)
	{
		return StartConditionErr;
	}
	else
	{
		return NOErr;
	}
}
TWI_ErrStatus TWI_Repeated_Start_Condition(){
	
	/* CLR Interrupt Flag, SET Start Condition Bit */
	TWCR_REG = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	
	if ((TWSR_REG & 0xf8) != REP_START)
	{
		return RepeatedStartErr;
	}
	else
	{
		return NOErr;
	}
}
TWI_ErrStatus TWI_Send_Slave_Address_With_Write(u8 copy_u8_address){
	
	TWDR_REG = (copy_u8_address<<1) & 0xfe;
	/* CLR Interrupt Flag, CLR Start Condition  */
	TWCR_REG = (1<<TWINT) | (1<<TWEN);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	if((TWSR_REG & 0xf8) != SLAVE_ADD_AND_WR_ACK)
	{
		return SlaveAddress_With_WriteErr;
	}
	else
	{
		return NOErr;
	}
}
TWI_ErrStatus TWI_Send_Slave_Address_With_Read(u8 copy_u8_address){
	
	TWDR_REG = (copy_u8_address<<1) | 0x01;
	/* CLR Interrupt Flag, CLR Start Condition  */
	TWCR_REG = (1<<TWINT) | (1<<TWEN);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	if((TWSR_REG & 0xf8) != SLAVE_ADD_AND_RD_ACK)
	{
		return SlaveAddress_With_ReadErr;
	}
	else
	{
		return NOErr;
	}
}
TWI_ErrStatus TWI_Master_Send_Data(u8 copy_u8_data){
	
	TWDR_REG = copy_u8_data;
	/* CLR Interrupt Flag */
	SET_BIT(TWCR_REG,TWINT);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	if((TWSR_REG & 0xf8) != MASTER_WR_BYTE_ACK)
	{
		return Master_Send_dataErr;
	}
	else
	{
		return NOErr;
	}
}
TWI_ErrStatus TWI_Master_Receive_Data(u8* copy_u8_data){
	SET_BIT(TWCR_REG,TWINT);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	if((TWSR_REG & 0xf8) != MASTER_RD_BYTE_WITH_NACK)
	{
		return Master_Recive_dataErr;
	}
	else
	{
		*copy_u8_data = TWDR_REG;
		return NOErr;
	}
}
TWI_ErrStatus TWI_Slave_ACK(){
	/* SET ACK */
	TWCR_REG = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	if((TWSR_REG & 0xf8) != SLAVE_ADD_RCVD_WD_REQ)
	{
		return TWI_Slave_ACKErr;
	}
	else
	{
		return NOErr;
	}
}
void TWI_Vid_Send_Stop_Condition(){
	/* CLR Interrupt Flag, SET Stop Condition */
	TWCR_REG = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}
u8 TWI_u8_Slave_Receive_Data(){
	
	TWCR_REG = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (GET_BIT(TWCR_REG,TWINT)==0);
	
	return TWDR_REG;
}