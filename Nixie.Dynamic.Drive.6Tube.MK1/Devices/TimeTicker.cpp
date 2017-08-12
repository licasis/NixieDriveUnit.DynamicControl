/* 
* TimeTicker.cpp
*
* Created: 2016-08-24 오전 1:57:31
* Author: Master
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TImeTicker.h"
#include "UART.h"
#define USING_INT2X

#ifndef USING_INT2
ISR(INT4_vect)
#else
ISR(INT2_vect)
#endif
{
	m_pDevices[NUM_TIMETICKER]->handle();
}


// default constructor
TimeTicker::TimeTicker()
{

} //TimeTicker

// default destructor
TimeTicker::~TimeTicker()
{
} //~TimeTicker
void TimeTicker::operator delete(void * p) // or delete(void *, std::size_t)
{

	//std::free(p);
}
void TimeTicker::init(void *param1,void *param2,void *param3)
{
	m_pParam[0] = param1;
	m_pParam[1] = param2;
	m_pParam[2] = param3;
#ifndef USING_INT2
	DDRE &= ~(1<<4);
	PORTE |= 1<<4;
	EICRB |= (1<< ISC41 |1 << ISC40 ); // falling edge detection
	EIMSK |=  1<<INT4;
#else
	DDRD &= ~(1<<2);
    PORTD |= 1<<2;
	EICRA |= (1<< ISC21 |1 << ISC20 ); 
	EIMSK |=  1<<INT2;
#endif	
}
void TimeTicker::handle()
{
	if(m_callback != 0)
		m_callback(m_pCallbackParam);
}
