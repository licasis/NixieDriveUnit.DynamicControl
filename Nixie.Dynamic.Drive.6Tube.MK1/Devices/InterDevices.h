/* 
* InterDevices.h
*
* Created: 2016-08-20 오후 12:30:19
* Author: Master
*/


#ifndef __INTERDEVICES_H__
#define __INTERDEVICES_H__
#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>

#define NUM_UART (0)
#define NUM_TIMETICKER (NUM_UART +1 )
#define NUM_DYNAMIC_DRIVER (NUM_UART +2 )
#define NUM_71414_DRIVER (NUM_UART +3 )
#define NUM_BRIGHT_CONTROL_DRIVER (NUM_UART +4 )
#define NUM_SWITCH_CONTROL_DRIVER (NUM_UART +5 )
#include "../Objects/ClockTime.h"
class InterDevices;
extern InterDevices *m_pDevices[100];
extern ClockTime *m_pclockTime;

typedef unsigned char BYTE;  

typedef int (* driverCallback)(void *);
class InterDevices
{
//functions
private:
protected:
	void *m_pParam[3];
	void *m_pCallbackParam;
	driverCallback m_callback;
public:
	InterDevices()
	{
		m_pParam[0]=m_pParam[1]=m_pParam[2]=m_pCallbackParam=0;
		m_callback = 0;
	};
	virtual ~InterDevices(){}
	virtual void init(void *,void *, void *)=0;
	virtual void handle()=0;
	virtual void regCallback(driverCallback,void *);

}; //InterDevices

#endif //__INTERDEVICES_H__
