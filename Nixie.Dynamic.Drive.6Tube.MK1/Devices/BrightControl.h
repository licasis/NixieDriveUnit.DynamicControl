/* 
* BrightControl.h
*
* Created: 2016-10-01 오전 12:30:32
* Author: Master
*/


#ifndef __BRIGHTCONTROL_H__
#define __BRIGHTCONTROL_H__
#include "InterDevices.h"

#define DEGREE_MARGIN 15
class BrightControl:public InterDevices
{
//variables
public:
protected:
private:

//functions
public:
	BrightControl();
	~BrightControl();
	virtual void init(void *,void *,void *);
	virtual void handle();
	int getDegree();
	int m_currentDegree;
protected:
private:
	BrightControl( const BrightControl &c );
	BrightControl& operator=( const BrightControl &c );
	void operator delete(void * p);
}; //BrightControl

#endif //__BRIGHTCONTROL_H__
