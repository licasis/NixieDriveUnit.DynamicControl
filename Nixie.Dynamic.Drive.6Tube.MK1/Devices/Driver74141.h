/* 
* Driver74141.h
*
* Created: 2016-08-20 오후 3:13:41
* Author: Master
*/


#ifndef __DRIVER74141_H__
#define __DRIVER74141_H__

#include "InterDevices.h"

#define _WAIT_BEFORE_CHANGE 100 // in micro second
#define IO_PORT_FOR_74141 PORTA
#define IO_DDR_FOR_74141 DDRA
class Driver74141:public InterDevices
{
//variables
public:
protected:
private:

//functions
public:
	Driver74141();
	~Driver74141();
	virtual void init(void *,void *,void *);
	virtual void handle();
	virtual void setOutput(BYTE);
protected:
private:
	Driver74141( const Driver74141 &c );
	Driver74141& operator=( const Driver74141 &c );
	void operator delete(void * p);
}; //Driver74141

#endif //__DRIVER74141_H__
