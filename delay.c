#include "delay.h"
void SetSystem72Mhz(void)
{
	// NHAN 9 VOI TAN SO 
	RCC->CFGR |= (7<<18); // or RCC->CFGR |= RCC_CFGR_PLLMULL9;
	// CHIA CHO 1.5 
	RCC->CFGR &= ~ (1<<22);
	// SET HSEON 
	RCC->CR |= (1<<16);
	// WAIT HSERDY 
	while((RCC->CR & RCC_CR_HSERDY)==0);
	// PLL FOR MODE HSE 
	RCC->CFGR |= (1<<16);
	
	// TUONG TU VOI HSE TA KICH HOAT PLLON VA CHO NO READY
	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY)==0);
	//Flash pre-fetch enable and wait-state=2
	  //0WS: 0-24MHz
	  //1WS: 24-48MHz
	  //2WS: 48-72MHz
	FLASH->ACR |= FLASH_ACR_PRFTBE|FLASH_ACR_LATENCY_1;
	 //Select PLL as main System Clock source
	RCC->CFGR &= ~ RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	//Wait until PLL system source is active
	while((RCC->CFGR & RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL);
	
	// AHB DIV1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	// APB1 DIV 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	// APP2 DIV 1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	// ADC PSC = 6 , 2X6 = 12 
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	// khong anh xa lai ma pin CHO TIM2 
	AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_NOREMAP;
	
}
void ConfigureTimer3(void)
{
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
  
  /* fCK_PSC / (PSC[15:0] + 1)
     (8 MHz / (7+1)) = 1 MHz timer clock speed */
  TIM3->PSC = 719;
  
  /* (1 MHz / 1000) = 1KHz = 1ms */
  /* So, this will generate the 1ms delay */
  TIM3->ARR = 99;
  
  /* Finally enable TIM3 module */
  TIM3->CR1 = (1 << 0);
}
void delay( uint32_t ms )
{
	uint32_t i;
  for( i = 0; i <= ms; i++ )
  {
    /* Clear the count */
    TIM3->CNT = 0;
    
    /* Wait UIF to be set */
    while((TIM3->SR & TIM_SR_UIF) == 0);    /* This will generate 1ms delay */
    
    /* Reset UIF */
    TIM3->SR &= ~TIM_SR_UIF;
  }
}
