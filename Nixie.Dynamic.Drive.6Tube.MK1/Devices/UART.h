/* 
* UART.h
*
* Created: 2016-08-20 오후 3:04:24
* Author: Master
*/


#ifndef __UART_H__
#define __UART_H__
#include "InterDevices.h"

class UART:public InterDevices
{
//variables
public:
protected:
private:

//functions
public:
	UART();
	~UART();
	virtual void init(void *,void *,void *);
	virtual void handle();
	virtual char getChar();
	virtual void putChar(char);
	virtual void putString(char *);

protected:
private:
	UART( const UART &c );
	UART& operator=( const UART &c );
	void operator delete(void * p);

}; //UART

#endif //__UART_H__
