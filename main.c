/*----------------------------------------------------------------------------
 *      PSTU KMU test board projects
 *----------------------------------------------------------------------------
 *      Name:    MAIN.C
 *      Purpose: Demo project for KMU test board: UART Echo test
 *      Rev.:    V1.00
 *----------------------------------------------------------------------------
 *      Author:	 			A. Sharonov
 *      Created:			28.04.2015
 *			Last modifed:	28.04.2015
 *---------------------------------------------------------------------------*/
 
#include <MDR32F9x.h>
#include <MDR32F9x_config.h>
#include "MDR32_UART.h"
#include "element.h"
#include <string.h>
#include "read_message.h"

unsigned char _cCountByte=0;
unsigned char _bDeviceIsConnected=0;
unsigned char _bPreambleIsSended=0;
char _cConnectedDeviceName[50];
char _cConnectedDeviceMacAddress[17];
extern unsigned char _message[2];
unsigned char _countPreambleByte=0;
unsigned char _countPostambleByte=0;
unsigned char _cCountByteInMessage=0;
unsigned char _cCountReadSocket=0;
unsigned char _bConnectedDeviceNameIsRead=0;
unsigned char _messageUart1[2];
unsigned char _cCountByteUart1;

void readSocket(unsigned char byte);

void frq_init(void)
{
	MDR_RST_CLK->HS_CONTROL = 0x1;                      /* Enable HSE oscillator     */
  while (MDR_RST_CLK->CLOCK_STATUS == 0x00) __NOP();  /* wait while HSE startup    */
  MDR_RST_CLK->CPU_CLOCK = 0x102;                     /* switch to HSE (8 MHz)     */	
	SystemCoreClockUpdate();                            /* Get Core Clock Frequency  */
}

int main (void)
{
	frq_init();
	UART1_init(9600); //USB-UART serial debug port
	UART1_int();
	UART2_init(9600); //bluetooth BTM-111 PF_19, PF_20
	UART2_int();
	while(1)
	{
		//send_string2("I'm ready!\r\n");
	}
}

void UART2_IRQHandler (void)
{
	unsigned char temp=0;
	
	temp=MDR_UART2->DR;
	//MDR_UART2->DR=temp;
	readSocket(temp);
	//MDR_UART1->DR=temp;
	//while (!(MDR_UART2->FR & (1UL << 7)));
	//while (!(MDR_UART1->FR & (1UL << 7))); //буфер передачика пуст (ждем пока данные отправятся из буфера передачика в порт)
}

void readSocket(unsigned char byte)
{
	_cCountReadSocket++;
	if(_bDeviceIsConnected)
  {
		_message[_cCountByte]=byte;
		_cCountByte++;
		if(_cCountByte>=2)
		{
			readMessage();
			_cCountByte=0;
		}
  }
  else
  {
      if(!_bPreambleIsSended)
      {
          if(byte==0xFF)
          {
						_countPreambleByte++;
            if(_countPreambleByte==8)
            {
              //преамбула получена, значит пора читать инфу
              _bPreambleIsSended=1;
							_countPreambleByte=0;
            }
					}
					else
						_countPreambleByte=0;

      }
      else
      {
          if(byte!=0xFF)
          {
						_countPostambleByte=0;
						
						//Читаем инфу о подключенном устройстве: имя и адрес
						if(byte==0x22) //разделитель между именем и адресом
						{
							_bConnectedDeviceNameIsRead=1;
							byte=' ';
						}
						if(!_bConnectedDeviceNameIsRead)
							strcat(_cConnectedDeviceName, (char *)&byte); //добавляем полученный байт в массив _cConnectedDeviceName
						
						if(_bConnectedDeviceNameIsRead && byte!=' ') //если имя прочитано, то читаем его мак-адрес
						{
							strcat(_cConnectedDeviceMacAddress, (char *)&byte);
						}
						
					}
					else
					{
						_countPostambleByte++;
						if(_countPostambleByte==8)
						{
							//инфа прочитана
							_bDeviceIsConnected=1;
							_countPostambleByte=0;
							//отправим имя и адрес подключенного устройства в UART1
							send_string1("\r\n");
							send_string1(_cConnectedDeviceName);
							send_string1("\t");
							send_string1(_cConnectedDeviceMacAddress);
							send_string1("\r\n");
						}
					}
       }
    }
}

void UART1_IRQHandler (void) //USB-UART console
{
	unsigned char temp=0;
	
	temp=MDR_UART1->DR;
	_messageUart1[_cCountByteUart1]=temp;
	_cCountByteUart1++;
	if(_cCountByteUart1>=2)
	{
		switch(_messageUart1[0])
		{
			case highTemperature:
				MDR_UART2->DR=0x82;
				while (!(MDR_UART2->FR & (1UL << 7)));
				if(_messageUart1[1]==on)
					MDR_UART2->DR=0x01;
				else
					MDR_UART2->DR=0x00;
				while (!(MDR_UART2->FR & (1UL << 7)));
				break;
			case hookWarning:
				MDR_UART2->DR=0x83;
				while (!(MDR_UART2->FR & (1UL << 7)));
				if(_messageUart1[1]==on)
					MDR_UART2->DR=0x01;
				else
					MDR_UART2->DR=0x00;
				while (!(MDR_UART2->FR & (1UL << 7)));
				break;
		}
		_cCountByteUart1=0;
	}
	MDR_UART1->DR=temp;
	while (!(MDR_UART1->FR & (1UL << 7)));//буфер передачика пуст (ждем пока данные отправятся из буфера передачика в порт)
}
