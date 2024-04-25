#ifndef USART_H
#define USART_H

#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <stm32f10x.h>

//Buffer
extern char USART1_RX[30];
extern uint8_t USART1_RX_Index; 
void USART1_Configure_GPIO(void);
void USART1_Configure_USART1(void);
void USART1_Configure_NVIC(void);
void USART1_Configuration(void);

void usart2_sendByte(unsigned char c);
void Config_uart2(void);
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data);
void USART_SendString(USART_TypeDef* USARTx, uint8_t *str);



#endif
