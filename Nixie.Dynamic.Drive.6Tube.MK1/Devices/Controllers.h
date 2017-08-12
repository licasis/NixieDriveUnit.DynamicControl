/* 
* Controllers.h
*
* Created: 2016-09-10 오후 12:14:49
* Author: Master
*/

#include "InterDevices.h"
#ifndef __CONTROLLERS_H__
#define __CONTROLLERS_H__


class Controllers:public InterDevices
{
//variables
public:
protected:
private:

//functions
public:
	Controllers();
	~Controllers();
	virtual void init(void *,void *,void *);
	virtual void handle();
protected:
private:
	Controllers( const Controllers &c );
	Controllers& operator=( const Controllers &c );
	void operator delete(void * p);
}; //Controllers

#endif //__CONTROLLERS_H__
