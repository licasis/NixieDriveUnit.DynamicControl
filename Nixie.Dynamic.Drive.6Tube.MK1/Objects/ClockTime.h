/* 
* ClockTime.h
*
* Created: 2016-08-20 오전 11:41:16
* Author: Master
*/


#ifndef __CLOCKTIME_H__
#define __CLOCKTIME_H__

#define HOUR_TYPE_12 (12)
#define HOUR_TYPE_24 (24)
#define MAKE_HIGH_4BIT(X) ( X>>4 )
#define MAKE_LOW_4BIT (X) (X & 0x0F)

typedef unsigned char Digit;
typedef struct t_TimeValue
{
	
	Digit Hour;
	Digit Minute;
	Digit Second;
}TimeValue;
class ClockTime
{
//variables
public:

protected:
private:
	Digit m_MaximumHour;
	TimeValue m_timeValue;
//functions
public:
	ClockTime();
	~ClockTime();
	void setMaximumHour(Digit maximum)
	{
		if((maximum != HOUR_TYPE_24 )||(maximum != HOUR_TYPE_12 ))
			m_MaximumHour = HOUR_TYPE_24;	
		m_MaximumHour = maximum;
		
	};
	void setTime(Digit H,Digit M,Digit S)
										{	
											m_timeValue.Hour = H;\
											m_timeValue.Minute = M;\
											m_timeValue.Second = S;
										};
	Digit getTimeHour(){return m_timeValue.Hour;};
	Digit getTimeMinute(){return m_timeValue.Minute;};
	Digit getTimeSecond(){return m_timeValue.Second;};
	void minuteUp();
	void hourUp();
			
	void FlyTime();
protected:
private:
	ClockTime( const ClockTime &c );
	ClockTime& operator=( const ClockTime &c );
}; //ClockTime

#endif //__CLOCKTIME_H__
