/* 
* Driver74141.cpp
*
* Created: 2016-08-20 오후 3:13:41
* Author: Master
*/


#include "Driver74141.h"

#include "UART.h"
#include "../Objects/ClockTime.h"
#include <util/delay.h>

#include <stdio.h>
// default constructor
Driver74141::Driver74141()
{
} //Driver74141

// default destructor
Driver74141::~Driver74141()
{
} //~Driver74141
void Driver74141::operator delete(void * p) // or delete(void *, std::size_t)
{

	//std::free(p);
}

void Driver74141::init(void *param1,void *param2,void *param3)
{
		IO_DDR_FOR_74141  |= 0x0F;
		IO_PORT_FOR_74141 |= 0x0F;
}
void Driver74141::handle()
{
	
	
}
void Driver74141::setOutput(BYTE value)
{
	//PORTX = value;
	char temp[100];

	
	
	#if 1

	//IO_PORT_FOR_74141 = ~(0x0F);  // clear low 4  bits first
	//IO_PORT_FOR_74141 |= (value & 0x0F); // then set 4 bit as its new value
	IO_PORT_FOR_74141 =value; // then set 4 bit as its new value
	
//	sprintf(temp ,"Value = 0x%x\n",data);
//	((UART*)m_pDevices[NUM_UART])->putString(temp);
	#else
	
	static BYTE currentValue = 0;
	static BYTE isFirst = 1;
	BYTE temp;
	if(isFirst & 1)
	{
		
		isFirst = 0;
	}
	else
	{

		temp = (currentValue & 0xF0) | (value & 0x0F);
		IO_PORT_FOR_74141 = temp;
		currentValue = temp;

	}
	
	#endif
}