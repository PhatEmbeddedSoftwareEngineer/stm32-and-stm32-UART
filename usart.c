#include "usart.h"

char USART1_RX[30];
uint8_t USART1_RX_Index=0;

/*
	function nay dung de cau hinh chan cho usart1 la chan so PB6 va PB7
*/
void USART1_Configure_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
	/*cau hinh uasrt1 tx PB6 la chan thay the push-pull*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	/*cau hinh usart1 rx PB7 la chan input floating*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	/*
		boi vi su dung chan 	PB6 va PB7 cho usart 1 khong phai chan mac dinh la PA9 va PA10 nen
		phai tien hanh anh xa lai chung
	*/
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
}

/*
	function nay dung de cau hinh cho usart1 cac che do ma no hoat dong toc do baud etc..
*/

void USART1_Configure_USART1(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	/*ngat usart1 rx */
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	/*run usart1*/
	USART_Cmd(USART1,ENABLE);
}

/*
	function nay dung de cau hinh ngat rx cho usart1
*/

void USART1_Configure_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/*muc do uu tien ngat cao nhat*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	/*cau hinh uu tien chinh cho kenh ngat, hien tai kenh ngat co muc do uu tien cao nhat trong cac kenh ngat*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART1_Configuration(void)
{
	USART1_Configure_GPIO();
	USART1_Configure_USART1();
	USART1_Configure_NVIC();
}
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data){
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
		USART_SendData(USARTx,data);	
}

void USART_SendString(USART_TypeDef* USARTx, uint8_t *str){
		while (*str)   { 
			 USART_SendChar(USARTx,*str); 
			 str++;
		}
}
void usart2_sendByte(unsigned char c)
{
	USART2->DR=c;
	while((USART2->SR&(1<<6))==0);
	USART2->SR &= ~ (1<<6);
	
}
void Config_uart2(void)
{
	RCC->APB1ENR |= (1<<17); // ENABLE USART2 
	RCC->APB2ENR |= 0xFC;
	// init usart2 
	GPIOA->CRL=0x44448B44; // TRUYEN RX2 KEO LEN TX2=ALT
	GPIOA->ODR |= (1<<3); // KEO LEN 
	USART2->CR1 = 0x200C;
	//DO LA USART2 NAM TRONG APB1ENR NEN LA 36MHZ 
	USART2->BRR = 3750;
	
}