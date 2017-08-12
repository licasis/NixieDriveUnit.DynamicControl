/* 
* TImeTicker.h
*
* Created: 2016-08-24 오전 1:57:31
* Author: Master
*/


#ifndef __TIMETICKER_H__
#define __TIMETICKER_H__
#include "InterDevices.h"

class TimeTicker:public InterDevices
{
//variables
public:
protected:
private:

//functions
public:
	TimeTicker();
	~TimeTicker();
	virtual void init(void *,void *,void *);
	virtual void handle();
protected:
private:
	TimeTicker( const TimeTicker &c );
	TimeTicker& operator=( const TimeTicker &c );
	void operator delete(void * p);
}; //TImeTicker

#endif //__TIMETICKER_H__
