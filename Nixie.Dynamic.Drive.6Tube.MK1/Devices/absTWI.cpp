/* 
* absTWI.cpp
*
* Created: 2016-10-02 오전 11:02:21
* Author: Master
*/


#include "absTWI.h"

#include <avr/io.h>
#include <util/delay.h>

// default constructor
int absTWI::m_isInited =0;
absTWI::absTWI():m_address(TWI_DEFAULT_ADDR)
{
	
} //absTWI

// default destructor
absTWI::~absTWI()
{
	
} //~absTWI

int absTWI::init()
{
	if(m_isInited != 0)
		return TWI_ERROR_INITIALIZED_ALREADY;
		
	DDRD |= 0x03; // set 1 at DDRD[0:1]
    PORTD &= ~(1);
	PORTD |= (1);
	
	TWSR |= (1 << TWPS0);
	TWBR = 0x12;
	TWCR = 1 <<TWEN;
	m_isInited = 1;
	return TWI_ERROR_OK;
}
int absTWI::_sequence_start()
{
	//TWI 인터럽트 플레그를 클리어 하기 우해 TWINT비트를 1로 설정
	//SDA 선로상 start를 보내기 위해 TWSTA 비트를 1로 설정
	//TWI를 초기화 하기 위해 TWEN 비트를 1fh tjfwjd
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	//start 시그널 전송이 완료되념 TWINT bit는 0으로 셋팅된다
	while((TWCR & (1<<TWINT))==0);
	
	//ACK bit 체크 start시그널을 성공적으로 전송했는지 검사

	int status = TWSR & 0xf8;
	switch(status)
	{
		case TW_REP_START:
		case TW_START:
			break;
		case TW_MT_ARB_LOST:
			return -1;
		default : 
			return -1;
	}
	return TWI_ERROR_OK;

}
int absTWI::_sequence_stop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	return TWI_ERROR_OK;
	
}
int absTWI::_sequence_address(int addr,OPCode readOrWrite)
{
	//주소의 황 7개 비트만 유효하다. 
	int timeout = TW_TIMEOUT;
	
	TWDR = ((addr<<1)&(0b11111110))|readOrWrite;
	//TWI 인터럽트 플레그를 클리어 하기 위해 TWINT 비트를 1로 설정
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	//전송이 완료되면 TWINT 비트는 1로 셋팅된다 , 즉 인터럽트 플레그가 세트된다
	while(timeout-- > 0)
	{
		if((TWCR &(1<<TWINT))!= 0)
			break;
	}
	if(timeout <=  0)
		return TWI_ERROR_TIMEOUT;
	int status = TWSR & 0xF8;
	switch(status)
	{
		case TW_MR_ADDR_ACK:
		case TW_MT_ADDR_ACK:
			return TWI_ERROR_OK;
	}
	return (status * -1);
}
int absTWI::_sequence_readData(unsigned char *data, int isLast)
{
	int timeout = TW_TIMEOUT;
	if(isLast)
		TWCR = (1<<TWINT) | (1<<TWEN);
	else
		TWCR= (1<<TWINT) | (1<<TWEN)| (1<<TWEA);
	
	while((timeout--) > 0)
	{
		if((TWCR & (1<<TWINT))!=0)
			break;
	}
	if(timeout <= 0)
		return TWI_ERROR_TIMEOUT;
	int status = TWSR & 0xF8;
	switch(status)
	{
		case TW_MR_DATA_ACK:
		case TW_MR_DATA_NACK:
			*data =TWDR;
			return TWI_ERROR_OK;
		return TWI_ERROR_OK;
	}
	return status * (-1);
}
int absTWI::_sequence_writeData(unsigned char data)
{
	//int timeout = TW_TIMEOUT;
	
	TWDR = data;
	
	TWCR = (1<<TWINT )| (1<<TWEN);
	
	while((TWCR & (1<<TWINT)) == 0);
	int status = TWSR & 0xF8;
	switch(status)
	{
		case TW_MT_DATA_ACK:
			return TWI_ERROR_OK;
	}
	return (status *(-1));
}
int absTWI::read(unsigned char *buffer , size_t length)
{
	int rtn;
	if(!m_isInited)
		return TWI_ERROR_NOT_INITIALIZED;
	if(m_address == TWI_DEFAULT_ADDR)
		return TWI_ERROR_NOT_READY;
	if(length <= 0)
		return TWI_ERROR_BUFFER_SIZE;
		
	rtn = _sequence_start();
	if(rtn != TWI_ERROR_OK)
	{
			_sequence_stop();
			goto ERROR_HANDLE;
	}
	rtn = _sequence_address(m_address,OPRead);
	if(rtn != TWI_ERROR_OK)
		goto ERROR_HANDLE;
	
	for(int i = 0; i<length;i++)
	{
		rtn = _sequence_readData(buffer +i);
		if(rtn != TWI_ERROR_OK)
			goto ERROR_HANDLE;
	}	
	rtn = _sequence_stop();
	if(rtn != TWI_ERROR_OK)
		goto ERROR_HANDLE;
	
	ERROR_HANDLE:
		return rtn;
}
int absTWI::write(unsigned char * buffer, size_t length)
{
	if(!m_isInited)
		return TWI_ERROR_NOT_INITIALIZED;
	if(m_address == TWI_DEFAULT_ADDR)
		return TWI_ERROR_NOT_READY;

	return TWI_ERROR_NOT_SUPPORTED;	
	
}