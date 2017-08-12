/* 
* DS3231.h
*
* Created: 2016-08-20 오후 3:05:01
* Author: Master
*/


#ifndef __DS3231_H__
#define __DS3231_H__
#include "absTWI.h"
#define _DS_MAXIMUM_POINTER 0x12
#define _DS_CONTROL_REGISTER_ADDR 0x0e
#define _DS_SECOND_REGISTER_ADDR 0x00
#define _DS_MINUTE_REGISTER_ADDR 0x01
#define _DS_HOUR_REGISTER_ADDR 0x02
#define GetHigh4Bit(x) ( (x>>4) & (0x0F))
#define GetLow4Bit(x) ( x & (0x0F))
#define MODE_12_HOUR 1
#define MODE_24_HOUR 0

typedef struct t_DS3231_Time
{
	unsigned char second:4;
	unsigned char second10:4;
	unsigned char minute:4;
	unsigned char minute10:4;
	unsigned char hour:4;
	unsigned char hour10:1;
	unsigned char hour20:1;
	unsigned char mode12Hour:1;
	unsigned char msb:1;
	
	
}DS3231_Time;
class DS3231:public absTWI
{
//variables
public:
protected:
private:

//functions
public:
	DS3231();
	~DS3231();
	int read(unsigned char *, size_t);
	int readRegs(unsigned char * , int , int , int * );
	int writeReg(int , unsigned char );
	int setMinute(int);
	int set1HzOn();
	int updateHour(int );
	int updateMinute(int );
	int updateSecond(int );
	int setupMode(int);
protected:
private:
	DS3231( const DS3231 &c );
	DS3231& operator=( const DS3231 &c );
	void operator delete(void *p){free(p);};
}; //DS3231

#endif //__DS3231_H__
