/* 
* Controllers.cpp
*
* Created: 2016-09-10 오후 12:14:49
* Author: Master
*/


#include "Controllers.h"
/*
ISR(INT4_vect)
{
	m_pDevices[NUM_TIMETICKER]->handle();
}

ISR(INT4_vect)
{
	m_pDevices[NUM_TIMETICKER]->handle();
}
*/

// default constructor
Controllers::Controllers()
{
} //Controllers

// default destructor
Controllers::~Controllers()
{
} //~Controllers

void Controllers::operator delete(void * p) // or delete(void *, std::size_t)
{
	//std::free(p);
}
void Controllers::init(void *,void *,void *)
{
	
}
void Controllers::handle()
{
	
}