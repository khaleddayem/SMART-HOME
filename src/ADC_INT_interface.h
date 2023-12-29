/*
 * ADC_interface.h
 *
 * Created: 9/16/2023 3:51:37 PM
 *  Author: Khaled AbdLdayem
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
/*===============================================================================================================*/
/* PRE-SCALER MODE */
#define  PRE_SCALER   SCALER_128
#define  SCALER_2     2
#define  SCALER_4     4
#define  SCALER_8     8
#define  SCALER_16    16
#define  SCALER_32    32
#define  SCALER_64    64
#define  SCALER_128   128
/*===============================================================================================================*/
/* REFERENCE MODE SELECTION */
#define  REFERENCE  AVCC
#define  AREF_EXT   1
#define  AVCC       2
#define  RESERVED   3
#define  AREF_INT   4
/*===============================================================================================================*/
/* CONVERSION MODE */
#define  CONVERSION_MODE      AUTO_TRIGGER
#define  AUTO_TRIGGER         0
#define  SINGLE_CONVERSION    1
/*===============================================================================================================*/
/* ADMUX REGISTER PINS MACROS */
#define  MUX0   0
#define  MUX1   1
#define  MUX2   2
#define  MUX3   3
#define  MUX4   4
#define  ADLAR  5
#define  REFS0  6
#define  REFS1  7
/*===============================================================================================================*/
/* ADCSRA REGISTER PINS MACROS */
#define  ADPS0   0      /* PRE_SCALER SELECT PIN0  */
#define  ADPS1   1      /* PRE_SCALER SELECT PIN0  */
#define  ADPS2   2      /* PRE_SCALER SELECT PIN0  */
#define  ADIE    3      /* ADC Interrupt Enable    */
#define  ADIF    4      /* ADC Interrupt Flag      */
#define  ADATE   5      /* ADC Auto Trigger Enable */
#define  ADSC    6      /* ADC Start Conversion    */
#define  ADEN    7      /* ADC Enable PIN0         */
/*===============================================================================================================*/
/* SFIOR REGISTER PINS MACROS */
#define  ADTS0    5      /* ADC Auto Trigger SOURCE SELCET PIN0 */
#define  ADTS1    6      /* ADC Auto Trigger SOURCE SELCET PIN1 */
#define  ADTS2    7      /* ADC Auto Trigger SOURCE SELCET PIN2 */
/*===============================================================================================================*/
/************************************************************************************************
* Function name  : ADC_Vid_Init
* Purpose        : ADC module Initialization
* Parameters     : void
* Return value   : void
************************************************************************************************/
void ADC_Vid_Init(void);
/************************************************************************************************
* Function name  : ADC_u16_Read
* Purpose        : READ the data to the ADC
* Parameters     : u8 copy_u8_chan
* Return value   : u16
************************************************************************************************/
void ADC_u16_Read(u8 copy_u8_ch);
/************************************************************************************************
* Function name  : ADC_Vid_Int_Enable
* Purpose        : ENABLE INTERRUPT ON ADC
* Parameters     : void
* Return value   : void
************************************************************************************************/
void ADC_Vid_Int_Enable(void);
/************************************************************************************************
* Function name  : ADC_Vid_Int_Disable
* Purpose        : DISABLE INTERRUPT ON ADC
* Parameters     : void
* Return value   : void
************************************************************************************************/
void ADC_Vid_Int_Disable(void);
/************************************************************************************************
* Function name  : ADC_Vid_Int_Setcallback
* Purpose        : CallBack Function
* Parameters     : void(*Fun1)(void)
* Return value   : void
************************************************************************************************/
void ADC_Vid_Int_Setcallback(void(*Fun1)(void));
/************************************************************************************************
* Function name  : ADC_Vid_Start
* Purpose        : Start Conversion
* Parameters     : void
* Return value   : void
************************************************************************************************/
void ADC_Vid_Start(void);
/************************************************************************************************
* Function name  : ADC_READ
* Purpose        : Read Data From ADC Register
* Parameters     : void
* Return value   : u16
************************************************************************************************/
u16 ADC_READ(void);




#endif /* ADC_INTERFACE_H_ */
