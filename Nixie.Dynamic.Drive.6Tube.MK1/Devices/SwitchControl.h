/* 
* SwitchControl.h
*
* Created: 2016-10-01 오전 1:05:19
* Author: Master
*/


#ifndef __SWITCHCONTROL_H__
#define __SWITCHCONTROL_H__
#include "InterDevices.h"
#define USE_INTERRUPT_SW

#ifdef USE_INTERRUPT_SW

#define PIN_MINUTE_UP INT5  // INT5 == PORTE5
#define PIN_HOUR_UP INT6    // INT6 == PORTE6

#define TIMER_ISR_MINUTE TIMER0_OVF_vect
#define TIMER_ISR_HOUR TIMER2_OVF_vect

#define DEBOUNCE_COUNT_HOUR 15 // timer ISR이 DEBOUNCE_COUNT만큼 반복해서 불리는동안 입력을 무시한다 (한번의 ISR 호출시간동안은 너무 짧다. ㅡㅜ
#define DEBOUNCE_COUNT_MINUTE DEBOUNCE_COUNT_HOUR

#else

#define PIN_MINUTE_UP PORTE5
#define PIN_HOUR_UP PORTE6


#endif

class SwitchControl:public InterDevices
{
//variables
public:
protected:
private:

//functions
public:
	SwitchControl();
	~SwitchControl();
	virtual void init(void *,void *,void *);
	virtual void handle();
	void hourUp();
	void MinuteUp();	
	int getState();
protected:
private:
	SwitchControl( const SwitchControl &c );
	SwitchControl& operator=( const SwitchControl &c );
	void operator delete(void * p);

}; //SwitchControl

#endif //__SWITCHCONTROL_H__
