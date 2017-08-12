/* 
* UART.cpp
*
* Created: 2016-08-20 오후 3:04:24
* Author: Master
*/

#include "DynamicTubeDriver.h"
#include "UART.h"
#include "Driver74141.h"
#include <avr/interrupt.h>
#include <avr/io.h>

ISR(USART1_RX_vect)
{
	char chKey = UDR1 ;
	static int tempDegree = 6;
	
	
	if(m_pclockTime == 0) return;
	if(m_pDevices[NUM_DYNAMIC_DRIVER] == 0) return;
				
	switch(chKey)
	{
		case 'h':
			m_pclockTime->hourUp();
			break;
		case 'm':
			m_pclockTime->minuteUp();
			break;
		case 'u':
			tempDegree=((DynamicTubeDriver*)m_pDevices[NUM_DYNAMIC_DRIVER])->setBright(tempDegree+1);
			((UART*)m_pDevices[NUM_UART])->putChar('0'+tempDegree);
			break;
		case 'd':
			tempDegree=((DynamicTubeDriver*)m_pDevices[NUM_DYNAMIC_DRIVER])->setBright(tempDegree-1);
			((UART*)m_pDevices[NUM_UART])->putChar('0'+tempDegree);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':((Driver74141 *)m_pDevices[NUM_71414_DRIVER])->setOutput(chKey-'0');
			break;
		
	}
}


// default constructor
UART::UART()
{
} //UART

// default destructor
UART::~UART()
{
} //~UART
void UART::init(void *param1,void *param2,void *param3)
{
	#if 1
	//DDRA = 0;
	//PORTA = 0;

	
	DDRD |= 0x1<<3; // 
	DDRD &= (~(0x1<<2));
	
	UCSR1A = 0x00; // ready flag clear
//	UCSR1B = 0x18; // rx,tx interrupt enable
	UCSR1B = 0x98; // rx,tx interrupt enable
	UCSR1C = 0x06; // tx data len 8bit
	UBRR1H = 0;
	UBRR1L = 8;  //baudrate is 115200
	#else
	unsigned char temp;
	unsigned int baudrate[15]={832, 416, 207, 138, 103, 68, 51, 34, 25, 16, 8, 7, 3, 1, 0};
	//DDRE = 0xFE; //시리얼통신을 위해 PE0핀은 RXD0로서 입력으로 설정하고, PE1 핀은 TXD0로서 출력으로 설정


	UBRR1H = baudrate[2]>>8; // 보레이트 설정 115200 bps

	UBRR1L = baudrate[2];


	UCSR1A = 0x02; // 비동기 모드, 더블 보레이트

	UCSR1B = 0x18; // 0x98 rx interrupt enable, 8 data, tx 0xD8, tx_empty 0xF8

	UCSR1C = 0x06; // no parity, 1 stop, 8 data

	temp = UDR1; // dummy read
	#endif
	
}
void UART::handle()
{
	
	
}
void UART::operator delete(void * p) // or delete(void *, std::size_t)
{
	//std::free(p);
}

char UART::getChar()
{
	while(!(UCSR1A&0x80)); // 수신완료될때까지 대기
	return UDR1;
}
void UART::putChar(char data)
{
	//PORTA=0x0FF;
	//_delay_ms(10);
	//PORTA = 0x00;
    while(!(UCSR1A&0x20)); // 송신데이터를 받을 준비가 될때까지 대기
    UDR1 = data;
}
void UART::putString(char *str)
{
	int index = 0 ;
	
	while(1)
	{
		if(str[index] == 0)
			break;
		else
		{
			    while(!(UCSR1A&0x20)); // 송신데이터를 받을 준비가 될때까지 대기
			    UDR1 = str[index];
		}
		index++;
	}
}
	