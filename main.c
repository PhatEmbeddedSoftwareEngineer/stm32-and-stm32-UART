#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
volatile int dem=0;
void USART1_IRQHandler(void){
		while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE)); 
				USART1_RX[USART1_RX_Index] = USART1->DR;
		if(USART1_RX[USART1_RX_Index]=='#'){
				USART1_RX[USART1_RX_Index+1]='\0';
				USART1_RX_Index=0;
				dem=1;
				
				//USART1_Command_Handler();
				//LCD_Display_USART1_RX();
		}
		else{
				USART1_RX_Index++;
		}
}
int main(void)
{
	SetSystem72Mhz();
	ConfigureTimer3();
	//SystemInit();
	USART1_Configuration();
	Config_uart2();
	//USART_SendChar(USART1,'P');
	char buffer[512];
	char luuTruSo[10];
	int value;
	
	
	while(1)
	{
		if(dem==1)
		{
			sprintf(buffer,"%s",USART1_RX);
			if(sscanf(buffer,"\npitch: %d#",&value))
			{
				int a=0;
				sprintf(luuTruSo,"gia tri data tach khoi chuoi la: %d",value);
				while(luuTruSo[a]!= '\0')
				{
					usart2_sendByte(luuTruSo[a]);
					a++;
				}
				usart2_sendByte('\n');	
				usart2_sendByte('\r');
			}
			/*
			int j=0;
			while(buffer[j] !='\0')
			{
				usart2_sendByte(buffer[j]);
				j++;
			}
			usart2_sendByte('\n');
			usart2_sendByte('\r');
			*/
			dem=0;
		}
		/*
		sprintf(buffer,"hello world %d",cnt+=1);
		int j=0;
		while(buffer[j] !='\0')
		{
			usart2_sendByte(buffer[j]);
			j++;
		}
		usart2_sendByte('\n');*/
		//usart2_sendByte('\r');
		//delay(500);
		/*
		sprintf(buffer,"\nhello world: %d",cnt+=1);
		USART_SendString(USART1,(uint8_t *)buffer);
		
		*/
	}
}