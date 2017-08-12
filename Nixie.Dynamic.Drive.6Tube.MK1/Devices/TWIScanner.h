/* 
* TWIScanner.h
*
* Created: 2016-10-03 오전 1:30:15
* Author: Master
*/


#ifndef __TWISCANNER_H__
#define __TWISCANNER_H__
#include <stdio.h>
#include <stdlib.h>
#define MAX_TWI_NODE_COUNT 128

#include "absTWI.h"

class TWIScanner:public absTWI
{
//variables
public:
protected:
private:
	int m_nfindedNode;
//functions
public:
	TWIScanner();
	~TWIScanner();
	int searchDevices();
	int getDeviceNumber();
	unsigned char getDeviceAddress(int);
protected:
private:
	unsigned char m_searchAddress[MAX_TWI_NODE_COUNT];
	TWIScanner( const TWIScanner &c );
	TWIScanner& operator=( const TWIScanner &c );
	void operator delete(void *p){free(p);};

}; //TWIScanner

#endif //__TWISCANNER_H__
