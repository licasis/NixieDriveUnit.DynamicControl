/* 
* SwitchControl.cpp
*
* Created: 2016-10-01 오전 1:05:19
* Author: Master
*/

//#define DEBOUNCE_COUNT_HOUR 15 // timer ISR이 DEBOUNCE_COUNT만큼 반복해서 불리는동안 입력을 무시한다 (한번의 ISR 호출시간동안은 너무 짧다. ㅡㅜ
//#define DEBOUNCE_COUNT_MINUTE DEBOUNCE_COUNT_HOUR

#include "SwitchControl.h"
#include "../Objects/ClockTime.h"
#include "UART.h"

#include <avr/io.h>
#include <avr/interrupt.h>
extern ClockTime *m_pclockTime;

volatile unsigned char g_DebouncingTimerMINUTECounter  =0 ;
volatile unsigned char g_DebouncingMINUTEFlag  =0 ;
volatile unsigned char g_DebouncingTimerHOURCounter  =0 ;
volatile unsigned char g_DebouncingHOURFlag  =0 ;

#ifdef USE_INTERRUPT_SW

ISR(INT5_vect)
{

	if(g_DebouncingMINUTEFlag==0)
	{
		g_DebouncingMINUTEFlag = 1; // 상태변경
		g_DebouncingTimerMINUTECounter = 0 ; //카운터 리셋
		TCNT0 = 0; // 카운터 레지스터 리셋
		TIFR &= ~(1<<TOV0); // (혹시나 걸렸을지도 모를....) 기존 Iterrupt flag를 초기화한다
		TIMSK |=TOIE0;
		((SwitchControl*)m_pDevices[NUM_SWITCH_CONTROL_DRIVER])->MinuteUp();
	}
	
}
ISR(INT6_vect)
{
	if(g_DebouncingHOURFlag==0)
	{
		g_DebouncingHOURFlag = 1; // 상태변경
		g_DebouncingTimerHOURCounter = 0 ; //카운터 리셋
		TCNT2 = 0; // 카운터 레지스터 리셋
		TIFR &= ~(1<<TOV2); // (혹시나 걸렸을지도 모를....) 기존 Iterrupt flag를 초기화한다
		TIMSK |=TOIE2;
		((SwitchControl*)m_pDevices[NUM_SWITCH_CONTROL_DRIVER])->hourUp();
	}

}


ISR(TIMER0_OVF_vect) // ISR for Debouncing Minute Switch
{
	;
	if(g_DebouncingTimerMINUTECounter >= DEBOUNCE_COUNT_MINUTE)
	{
		g_DebouncingMINUTEFlag = 0;
		TIMSK &= ~(1<<TOIE0);
	}
	else
		g_DebouncingTimerMINUTECounter++;
}
ISR(TIMER2_OVF_vect) //ISR for Debouncing Minute Switch
{
	if(g_DebouncingTimerHOURCounter >= DEBOUNCE_COUNT_HOUR)
	{
		g_DebouncingHOURFlag = 0;
		TIMSK &= ~(1<<TOIE2);
	}
	else
	g_DebouncingTimerHOURCounter++;
}
	
#endif
// default constructor
SwitchControl::SwitchControl()
{
} //SwitchControl

// default destructor
SwitchControl::~SwitchControl()
{
} //~SwitchControl
void SwitchControl::operator delete(void * p) // or delete(void *, std::size_t)
{

	//std::free(p);
}
void SwitchControl::init(void *param1,void *param2,void *param3)
{
#ifdef USE_INTERRUPT_SW
    // SWITCH IO SETTING
	
	DDRE &= ~(1<<PIN_HOUR_UP | 1<<PIN_MINUTE_UP); // INPUT Mode
	PORTE |= 1<<PIN_HOUR_UP | 1<<PIN_MINUTE_UP;  // PULL up , default state is High, 
	EICRB |= 1<<ISC51 ;
	EICRB |= 1<<ISC61; // Falling edge detection for PIN_HOUR_UP and PIN_MINUTE_UP
	EIMSK |= 1 << PIN_MINUTE_UP | 1<<PIN_HOUR_UP;
	
	// TIMER INIT FOR Debouncing
	TCCR0 = (1<<CS02)|(1<<CS01)|(1<<CS00); // Timer0 Pre Scaler = 1024 
	TCCR2 = (1<<CS22)|(1<<CS21)|(1<<CS20); // Timer2 Pre Scaler = 1024 
	
#else 
	DDRE &= ~(1<<PIN_HOUR_UP | 1<<PIN_MINUTE_UP); // INPUT Mode
	PORTE |= ( 1<<PIN_HOUR_UP );  // PULL up , default state is High, 
	PORTE |= 1<<(PIN_MINUTE_UP);
	
#endif
	
}
void SwitchControl::handle()
{

}
void SwitchControl::hourUp()
{
	if(m_pclockTime != NULL)
		m_pclockTime->hourUp();
}
void SwitchControl::MinuteUp()
{
	if(m_pclockTime != NULL)
		m_pclockTime->minuteUp();
}
int SwitchControl::getState()
{
	volatile int temp = PINE;
	int rtn = 0x0;
	if((temp & (1 << PIN_HOUR_UP))==0)
		rtn |= 0x1 <<4;
	if((temp & (1 << PIN_MINUTE_UP))==0)
		rtn |= 0x1;
	return rtn;
}