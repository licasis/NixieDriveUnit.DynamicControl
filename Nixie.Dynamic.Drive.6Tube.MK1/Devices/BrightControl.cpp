/* 
* BrightControl.cpp
*
* Created: 2016-10-01 오전 12:30:32
* Author: Master
*/


#include "BrightControl.h"
#include "UART.h"


#include <stdio.h>


#define DDR_BRIGHT_CONTROL DDRF
#define PIN_BRIGHT_CONTROL PINF0
#define PORT_BRIGHT_CONTROL PORTF
// default constructor
int DegreeRangeLowTable[10]={0,100,200,300,400,500,600,700,800,900};
int DegreeRangeHighTable[10]={100,200,300,400,500,600,700,800,900,1024};
BrightControl::BrightControl():m_currentDegree(1)
{
} //BrightControl

// default destructor
BrightControl::~BrightControl()
{
} //~BrightControl
void BrightControl::operator delete(void * p) // or delete(void *, std::size_t)
{

	//std::free(p);
}
void BrightControl::init(void *param1,void *param2,void *param3)
{
	DDR_BRIGHT_CONTROL &= ~(1); // input mode for PORTF0
	
}
void BrightControl::handle()
{

}
int BrightControl::getDegree()
{
	volatile int current;
	int tempDegree = 0;
	ADMUX = 1<<REFS0; // Use AVCC as reference voltage souce
	ADCSRA = 0xc7; // adc enable , start , prescale 128
	while(ADCSRA & (1<<ADIF) == 1);
	current = ADC;

	if((current >= (DegreeRangeLowTable[0]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[0] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 0;
	}
	else if((current >= (DegreeRangeLowTable[1]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[1] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 1;
	}
	else if((current >= (DegreeRangeLowTable[2]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[2] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 2;
	}
	
	else if((current >= (DegreeRangeLowTable[3]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[3] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 3;
	}
	
	else if((current >= (DegreeRangeLowTable[4]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[4] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 4;
	}
	
	else if((current >= (DegreeRangeLowTable[5]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[5] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 5;
	}
	
	else if((current >= (DegreeRangeLowTable[6]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[6] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 6;
	}
	
	else if((current >= (DegreeRangeLowTable[7]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[7] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 7;
	}
	
	else if((current >= (DegreeRangeLowTable[8]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[8] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 8;
	}
	
	else if((current >= (DegreeRangeLowTable[9]- DEGREE_MARGIN)) && (current <  (DegreeRangeHighTable[9] + DEGREE_MARGIN))  )
	{
		m_currentDegree = 9;
	}

	return m_currentDegree ;
}
