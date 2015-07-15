#include <MDR32F9x.h>
#include "MDR32F9x_config.h"

void UART2_init (unsigned int bnd)
{
	//I/O ports init
	MDR_RST_CLK->PER_CLOCK 	|=(1<<29);//Разрешаем тактирование порта F
	MDR_PORTF->OE						|=0x0002;//PF1 на выход (TxD)
	MDR_PORTF->FUNC					|=0x0000000F; //Назначаем функций UART
	MDR_PORTF->ANALOG				|=0x0003;//Переводим пины в цифровой режим
	MDR_PORTF->PWR					|=0x0000000F;//Устанавливаем самый быстрый фронт
	
	//UART2 interface init
	MDR_RST_CLK->PER_CLOCK	|=(1<<7);//Разрешаем тактирование UART в PER_CLOCK
	MDR_RST_CLK->UART_CLOCK	|=(1<<25);//Еще раз разрешаем тактирование UART - в UART_CLOCK
	MDR_UART2->IBRD					=8000000/(16*bnd);//Настраиваем скорость - целую часть
	MDR_UART2->FBRD					=(8000000*64/(16*bnd))-((8000000/(16*bnd))*64);//Настраиваем скорость - дробную часть

	MDR_UART2->LCR_H				=0x60;//Передавать будем 8 бит
	MDR_UART2->CR						=0x0300;//Разрешаем приемник и передатчик
	MDR_UART2->CR						|=0x0001;//Запускаем UART
}

void UART1_init (unsigned int bnd)
{
	//I/O ports init
	MDR_RST_CLK->PER_CLOCK 	|=(1<<22);
	MDR_PORTB->OE						|=1<<5;
	MDR_PORTB->FUNC					|=0x00002800;
	MDR_PORTB->ANALOG				|=0x0060;
	MDR_PORTB->PWR					|=0x00003C00;
	
	//UART1 interface init
	MDR_RST_CLK->PER_CLOCK	|=(1<<6);
	MDR_RST_CLK->UART_CLOCK	|=(1<<24);
	MDR_UART1->IBRD					=8000000/(16*bnd);
	MDR_UART1->FBRD					=(8000000*64/(16*bnd))-((8000000/(16*bnd))*64);

	MDR_UART1->LCR_H				=0x60;
	MDR_UART1->CR						=0x0300;
	MDR_UART1->CR						|=0x0001;
}

void UART2_int (void)
{
	//UART2 interface IRQ init
	NVIC_EnableIRQ(UART2_IRQn);
	MDR_UART2->IMSC					=0x0010;	//??
}
void UART1_int (void)
{
	//UART2 interface IRQ init
	NVIC_EnableIRQ(UART1_IRQn);
	MDR_UART1->IMSC					=0x0010;	 //??
}


void send_string2 (char *str)
{
	unsigned int t=0;
	
	while (str[t])
	{
		MDR_UART2->DR = (str[t]);
		while (!(MDR_UART2->FR & (1UL << 7)));
		t++;
	}
}

void send_string1 (char *str)
{
	unsigned int t=0;
	
	while (str[t])
	{
		MDR_UART1->DR = (str[t]);
		while (!(MDR_UART1->FR & (1UL << 7)));
		t++;
	}
}
