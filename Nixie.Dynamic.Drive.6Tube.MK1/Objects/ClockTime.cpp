/* 
* ClockTime.cpp
*
* Created: 2016-08-20 오전 11:41:16
* Author: Master
*/


#include "ClockTime.h"

// default constructor
ClockTime::ClockTime()
{
	m_MaximumHour = HOUR_TYPE_24;
	m_timeValue.Hour = m_timeValue.Minute = m_timeValue.Second = 0;
	
} //ClockTime

// default destructor
ClockTime::~ClockTime()
{
} //~ClockTime

void ClockTime::FlyTime()
{
	if(m_timeValue.Second == 59)
	{
		if(m_timeValue.Minute == 59)
		{
			if(m_timeValue.Hour == (m_MaximumHour-1)) // Maximum hour 
			{
				m_timeValue.Hour = 0;
				
			}
			else
			{
				m_timeValue.Hour++;
			}
			m_timeValue.Minute = 0;
		}
		else
		{
			m_timeValue.Minute++;	
		}
		m_timeValue.Second = 0	;	
	}
	else
		m_timeValue.Second++;
}

void ClockTime::minuteUp()
{

		
		if(m_timeValue.Minute == 59)
		{
			if(m_timeValue.Hour == m_MaximumHour-1)
				m_timeValue.Hour = 0;
			else
				m_timeValue.Hour++;
			m_timeValue.Minute = 0;
		}
		else
			m_timeValue.Minute++;
}
void ClockTime::hourUp()
{

	if(m_timeValue.Hour == m_MaximumHour-1)
		m_timeValue.Hour = 0;
	else
		m_timeValue.Hour++;	
}