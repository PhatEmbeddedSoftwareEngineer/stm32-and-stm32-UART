#ifndef DELAY_H
#define DELAY_H

#include "stm32f10x.h"                  // Device header
void SetSystem72Mhz(void);
void ConfigureTimer3(void);
void delay( uint32_t ms );


#endif