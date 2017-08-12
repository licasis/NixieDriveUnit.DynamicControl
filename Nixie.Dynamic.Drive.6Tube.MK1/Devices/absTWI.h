/* 
* absTWI.h
*
* Created: 2016-10-02 오전 11:02:21
* Author: Master
*/


#ifndef __ABSTWI_H__
#define __ABSTWI_H__

#include <stdio.h>
#include <stdlib.h>

#define TWI_DEFAULT_ADDR (1<<7)

#define TW_START 0x08
#define TW_REP_START 0x10
#define TW_TIMEOUT 20000
// Master Transmitter mode

#define TW_MT_ADDR_ACK 0x18 //SLA+W transmitted , ACK received
#define TW_MT_ADDR_NACK 0x20 // 
#define TW_MT_DATA_ACK 0x28
#define TW_MT_DATA_NACK 0x30
#define TW_MT_ARB_LOST 0x38

// Master Receiver mode 

#define TW_MR_ARB_LOST 0x38
#define TW_MR_ADDR_ACK 0x40
#define TW_MR_ADDR_NACK 0x48
#define TW_MR_DATA_ACK 0x50
#define TW_MR_DATA_NACK 0x58

#define TWI_ERROR_OK 0
#define TWI_ERROR_NOT_READY -1
#define TWI_ERROR_INITIALIZED_ALREADY -3
#define TWI_ERROR_NOT_INITIALIZED -4
#define TWI_ERROR_TIMEOUT -5

#define TWI_ERROR_NOT_SUPPORTED -100
#define TWI_ERROR_BUFFER_SIZE -200

#define TWI_ERROR_MR_ARB_LOST (TW_MR_ARB_LOST * -1)
#define TWI_ERROR_MR_ADDR_ACK (TW_MR_ADDR_ACK * -1)
#define TWI_ERROR_MR_ADDR_NACK (TW_MR_ADDR_NACK * -1)
#define TWI_ERROR_MR_DATA_ACK (TW_MR_DATA_ACK * -1)
#define TWI_ERROR_MR_DATA_NACK (TW_MR_DATA_NACK * -1)

class absTWI
{
//variables
public:
	static int m_isInited;
	unsigned char m_address;
	enum OPCode{OPWrite , OPRead};
	void operator delete(void * p);
	virtual int read(unsigned char * , size_t);
	virtual int write(unsigned char * , size_t);
	int init();
	int setAddress(unsigned int addr){m_address = addr;return m_address;};
	virtual int _sequence_start();
	virtual int _sequence_stop();
	virtual int _sequence_address(int,OPCode);
	virtual int _sequence_readData(unsigned char *, int isLast =0);
	virtual int _sequence_writeData(unsigned char);
	
protected:
private:

//functions
public:
	absTWI();
	~absTWI();
protected:
private:
	absTWI( const absTWI &c );
	absTWI& operator=( const absTWI &c );

}; //absTWI

#endif //__ABSTWI_H__
