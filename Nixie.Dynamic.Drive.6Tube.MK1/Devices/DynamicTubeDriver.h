/* 
* DynamicTubeDriver.h
*
* Created: 2016-08-26 오전 1:46:11
* Author: Master
*/


#ifndef __DYNAMICTUBEDRIVER_H__
#define __DYNAMICTUBEDRIVER_H__
#define TUBE_COUNT 6
#include <avr/io.h>
#include <stdio.h>
#include "InterDevices.h"


#define IO_PORT_FOR_DYNAMIC_SWITCH PORTC
#define IO_DDR_FOR_DYNAMIC_SWITCH DDRC


#define TUBE_DRIVER_OFF 0
#define TUBE_DRIVER_ON 1


#define MAX_BRIGHT_DEGREE 9

#define MIN_BRIGHT_DEGREE 0

#define DELAY_NS_FOR_TUBE_DRIVE 200


class DynamicTubeDriver:public InterDevices
{
//variables
public:
protected:
private:
	unsigned char m_brightDegree;
	unsigned char m_flagOnOff;
	unsigned char m_tube[TUBE_COUNT];
	unsigned char m_currentTube;
//functions
public:
	DynamicTubeDriver();
	~DynamicTubeDriver();
	virtual void init(void *,void *,void *);
	virtual void handle();
	void driveOn(){m_flagOnOff =TUBE_DRIVER_OFF ;  };
	void driveOff(){m_flagOnOff =TUBE_DRIVER_ON ;  };
	void driveNextTube();
	int setBright(int );
	void operator delete(void * p);
protected:
private:
	DynamicTubeDriver( const DynamicTubeDriver &c );
	DynamicTubeDriver& operator=( const DynamicTubeDriver &c );

}; //DynamicTubeDriver

#endif //__DYNAMICTUBEDRIVER_H__
