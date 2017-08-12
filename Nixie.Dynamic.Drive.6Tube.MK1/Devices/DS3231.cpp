/* 
* DS3231.cpp
*
* Created: 2016-08-20 오후 3:05:01
* Author: Master
*/


#include "DS3231.h"
#include "UART.h"
// default constructor
DS3231::DS3231()
{
} //DS3231

// default destructor
DS3231::~DS3231()
{
} //~DS3231

int DS3231::read(unsigned char * buffer, size_t length)
{
	return TWI_ERROR_OK;
}
int DS3231::setupMode(int mode)
{
	
	unsigned char  data[3];
	int readData=0;
	int newHour;
	DS3231_Time *pTimeData;
	readRegs(data, _DS_HOUR_REGISTER_ADDR, 3, &readData);
	pTimeData = (DS3231_Time *)data;
	if(pTimeData->mode12Hour!=MODE_12_HOUR) 
		return 0;
	//if its mode is not 24Hour , clear time keeping.
	data[0]=0x00;
	writeReg(_DS_HOUR_REGISTER_ADDR,data[0]);
	writeReg(_DS_MINUTE_REGISTER_ADDR,data[0]);
	writeReg(_DS_SECOND_REGISTER_ADDR,data[0]);
	readRegs(data, _DS_HOUR_REGISTER_ADDR, 1, &readData ); // to be sure operating writeReg, just read one more.
	
}
int DS3231::readRegs(unsigned char * buffer, int address, int length, int * readsize )
{
	int rtn;
	int index=0;
	unsigned char logger[100];
	unsigned char data;
	int available = _DS_MAXIMUM_POINTER;
	available -= address ;// 이상하게도 define값을 집접 연산하면 되지 않는다 , 아마도 상수화 처리되어서 연산을 안하는듯... 먼저 변수에 담고 그다음에 빼줘야함
	if(available < length)
		length = available;
		
		*readsize = length;
		
		if(!m_isInited)
			return TWI_ERROR_NOT_INITIALIZED;
		if(m_address == TWI_DEFAULT_ADDR)
			return TWI_ERROR_NOT_READY;
		
		rtn = _sequence_start();
		if(rtn != TWI_ERROR_OK)
		{
			_sequence_stop();
			((UART*)m_pDevices[NUM_UART])->putString("ERROR HERE -1");while(1);
			goto ERROR_HANDLE;		
		}
		rtn = _sequence_address(m_address,OPWrite);
		if(rtn != TWI_ERROR_OK)
		{
		//	_sequence_stop();
			((UART*)m_pDevices[NUM_UART])->putString("ERROR HERE -2");while(1);
			goto ERROR_HANDLE;
		}
		rtn = _sequence_writeData(address);
		if(rtn != TWI_ERROR_OK)
		{
			_sequence_stop();
			((UART*)m_pDevices[NUM_UART])->putString("ERROR HERE -3");while(1);
			goto ERROR_HANDLE;
		}
		
		rtn = _sequence_start(); // repeat start
		if(rtn != TWI_ERROR_OK)
		{
			_sequence_stop();
			goto ERROR_HANDLE;
		}
		rtn = _sequence_address(m_address, OPRead);
		if(rtn != TWI_ERROR_OK)
		{
			((UART*)m_pDevices[NUM_UART])->putString("ERROR HERE -4");while(1);
			_sequence_stop();
			goto ERROR_HANDLE;
		}
		
		for(index = 0; index< length ; index++)
		{
			rtn = _sequence_readData(buffer + index ,(length == (index +1))?1:0);
			if(rtn != TWI_ERROR_OK)
			{	
				;
			}
			else
			{
				;
			}
		}
		if(rtn != TWI_ERROR_OK)
			goto ERROR_HANDLE;
		
		rtn = _sequence_stop();
		if(rtn != TWI_ERROR_OK)
			goto ERROR_HANDLE;

		return TWI_ERROR_OK;
ERROR_HANDLE:		
		return rtn;
}
int DS3231::writeReg(int address, unsigned char data)
{
	
	int rtn;
	if(! m_isInited)
	return TWI_ERROR_NOT_INITIALIZED;
	if(m_address == TWI_DEFAULT_ADDR)
	return TWI_ERROR_NOT_READY;

	rtn = _sequence_start();
	if(rtn != TWI_ERROR_OK)
	{
		_sequence_stop();
		goto ERROR_HANDLE;
	}
	rtn = _sequence_address(m_address,OPWrite);
	if(rtn != TWI_ERROR_OK)
	{
		_sequence_stop();
		goto ERROR_HANDLE;
	}
	rtn = _sequence_writeData(address);
	if(rtn != TWI_ERROR_OK)
	{
		_sequence_stop();
		goto ERROR_HANDLE;
	}

	rtn = _sequence_writeData(data);
	if(rtn != TWI_ERROR_OK)
	{
		_sequence_stop();
		goto ERROR_HANDLE;
	}

	rtn = _sequence_stop();
	if(rtn != TWI_ERROR_OK)
	{
		goto ERROR_HANDLE;
	}

	return TWI_ERROR_OK;
ERROR_HANDLE:
	return rtn;
}
int DS3231::setMinute(int)
{
	
	return TWI_ERROR_OK;
}
int DS3231::set1HzOn()
{
	unsigned char data;
	int readsize = -1;
	readRegs(&data,_DS_CONTROL_REGISTER_ADDR,1,&readsize);
	data &= (~(1<<2 | 1<<3 |1<<4 ));
	return writeReg(_DS_CONTROL_REGISTER_ADDR,data);
}
int DS3231::updateHour(int value)
{
	char Buffer[100];
	//sprintf(Buffer,"updateHour start  = %d \r\n",value);
	//((UART*)m_pDevices[NUM_UART])->putString(Buffer);
	unsigned char data=0x00;
	//sprintf(Buffer,"updateHour end-0 0x%02x  , value = %d\r\n",data,value);
	//((UART*)m_pDevices[NUM_UART])->putString(Buffer);
	if(value >=20)
	{
		data|=1<<5;
		value -=20;
	}
	//sprintf(Buffer,"updateHour end-1 0x%02x  , value = %d\r\n",data,value);
	//((UART*)m_pDevices[NUM_UART])->putString(Buffer);
	if(value >= 10)
	{
		data|=1<<4;
		value -=10;
	}
	//sprintf(Buffer,"updateHour end-2 0x%02x  , value = %d\r\n",data,value);
	//((UART*)m_pDevices[NUM_UART])->putString(Buffer);
	data|=(0x0F&value);
	//sprintf(Buffer,"updateHour end-3 0x%02x  , value = %d\r\n",data,value);
	//((UART*)m_pDevices[NUM_UART])->putString(Buffer);
	return writeReg(_DS_HOUR_REGISTER_ADDR,data);
		
}
int DS3231::updateMinute(int value)
{

	unsigned char high;
	unsigned char low;
	low = (value %10);
	high = ((value - low)/10)<<4;
	low = high|low;
	return writeReg(_DS_MINUTE_REGISTER_ADDR,low);
	
}
int DS3231::updateSecond(int value)
{
	unsigned char high;
	unsigned char low;
	low = (value %10);
	high = ((value - low)/10)<<4;
	low = high|low;
	return writeReg(_DS_SECOND_REGISTER_ADDR,low);		
}