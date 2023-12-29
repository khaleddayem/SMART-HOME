/*
 * TWI_interface.h
 *
 * Created: 11/15/2023 9:58:51 PM
 *  Author: Mazen
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

typedef enum
{
	NOErr,
	StartConditionErr,
	RepeatedStartErr,
	SlaveAddress_With_WriteErr,
	SlaveAddress_With_ReadErr,
	Master_Send_dataErr,
	Master_Recive_dataErr,
	TWI_Slave_ACKErr,
	
}TWI_ErrStatus;

void TWI_Vid_Master_Init(u8 copy_u8_address);
void TWI_Vid_Slave_Init(u8 copy_u8_address);
TWI_ErrStatus TWI_Send_Start_Condition();
TWI_ErrStatus TWI_Repeated_Start_Condition();
TWI_ErrStatus TWI_Send_Slave_Address_With_Write(u8 copy_u8_address);
TWI_ErrStatus TWI_Send_Slave_Address_With_Read(u8 copy_u8_address);
TWI_ErrStatus TWI_Master_Send_Data(u8 copy_u8_data);
TWI_ErrStatus TWI_Master_Receive_Data(u8* copy_u8_data);
TWI_ErrStatus TWI_Slave_ACK();
void TWI_Vid_Send_Stop_Condition();
u8 TWI_u8_Slave_Receive_Data();



#endif /* I2C_INTERFACE_H_ */