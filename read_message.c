#include "read_message.h"
#include "MDR32_UART.h"
#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>

unsigned char _message[2];

char* itoa(int value, char* result, int base) 
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }
    
    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;
    
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );
    
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
	
void readMessage()
{
	switch(_message[0])
	{
		case powerButton:
			setPower(_message[1]);
			break;
		case lightButton:
			setLight(_message[1]);
			break;
		case soundSignal:
			setSound(_message[1]);
			break;
		case speedButton:
			setSpeed(_message[1]); //в данный момент данная команда не посылается с пульта (отключена) -  регулировка скорости происходит по скорости отправки пакетов
			break;
		case pillarUp:
			setPillarUp(_message[1]);
			break;
		case pillarDown:
			setPillarDown(_message[1]);
			break;
		case derrickUp:
			setDerrickUp(_message[1]);
			break;
		case derrickDown:
			setDerrickDown(_message[1]);
			break;
		case outriggerUp:
			setOutriggerUp(_message[1]);
			break;
		case outriggerDown:
			setOutriggerDown(_message[1]);
			break;
		case telescopicUp:
			setTelescopicUp(_message[1]);
			break;
		case telescopicDown:
			setTelescopicDown(_message[1]);
			break;
		case hookUp:
			setHookUp(_message[1]);
			break;
		case hookDown:
			setHookDown(_message[1]);
			break;
		case leftCrutchUp:
			setLeftCrutchUp(_message[1]);
			break;
		case leftCrutchDown:
			setLeftCrutchDown(_message[1]);
			break;
		case rightCrutchUp:
			setRightCrutchUp(_message[1]);
			break;
		case rightCrutchDown:
			setRightCrutchDown(_message[1]);
			break;
		case incorrectCommand:
			break;
		default:
			break;
	}
}

void setPower(unsigned char status)
{
	if(status)
	{
		//поступила команда "включить питание"
		send_string1("P1\r\n");
	}
	else
	{
		//поступила команда "выключить питание"
		send_string1("P0\r\n");
	}
}

void setLight(unsigned char status)
{
	if(status)
	{
		//поступила команда "включить свет"
		send_string1("L1\r\n");
	}
	else
	{
		//поступила команда "выключить свет"
		send_string1("L0\r\n");
	}
}

void setSound(unsigned char status)
{
	if(status)
	{
		//поступила команда "гудок"
		send_string1("S1\r\n");
	}
	else
	{
		//поступила команда "гудок"
		send_string1("S0\r\n");
	}
}

void setSpeed(unsigned char status)
{
	if(status)
	{
		//поступила команда "скорость-быстро"
		send_string1("N1\r\n"); //N-Nitro!!! :)
	}
	else
	{
		//поступила команда "скорость-медленно"
		send_string1("N0\r\n");
	}
}

void makeCharSpeedElement(char *str, unsigned char status)
{
	switch(status)
	{
		case 0x00:
			strcat(str, "0");
			break;
		case 0x01:
			strcat(str, "1");
			break;
		case 0x02:
			strcat(str, "2");
			break;
		case 0x03:
			strcat(str, "3");
			break;
		case 0x04:
			strcat(str, "4");
			break;
		case 0x05:
			strcat(str, "5");
			break;
		case 0x06:
			strcat(str, "6");
			break;
		case 0x07:
			strcat(str, "7");
			break;
		case 0x08:
			strcat(str, "8");
			break;
		case 0x09:
			strcat(str, "9");
			break;
		case 0x0A:
			strcat(str, "10");
			break;
	}
}

void setPillarUp(unsigned char status)
{
	char str[7]="PUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}

void setPillarDown(unsigned char status)
{
	char str[9]="PDown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}

void setDerrickUp(unsigned char status)
{
	char str[7]="DUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}

void setDerrickDown(unsigned char status)
{
	char str[9]="DDown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setOutriggerUp(unsigned char status)
{
	char str[7]="OUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setOutriggerDown(unsigned char status)
{
	char str[9]="ODown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setTelescopicUp(unsigned char status)
{
	char str[7]="TUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setTelescopicDown(unsigned char status)
{
	char str[9]="TDown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setHookUp(unsigned char status)
{
	char str[7]="HUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setHookDown(unsigned char status)
{
	char str[9]="HDown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setLeftCrutchUp(unsigned char status)
{
	char str[8]="LCUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setLeftCrutchDown(unsigned char status)
{
	char str[10]="LCDown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setRightCrutchUp(unsigned char status)
{
	char str[8]="RCUp";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}
void setRightCrutchDown(unsigned char status)
{
	char str[10]="RCDown";
	makeCharSpeedElement(str, status);
	strcat(str, "\r\n");
	send_string1(str);
}

