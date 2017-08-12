/* 
* TWIScanner.cpp
*
* Created: 2016-10-03 오전 1:30:14
* Author: Master
*/


#include "TWIScanner.h"

// default constructor
TWIScanner::TWIScanner()
{
	for(int i =0;i<MAX_TWI_NODE_COUNT;i++)
	{
		m_searchAddress[i] = TWI_DEFAULT_ADDR;
	}
	m_nfindedNode = 0;
} //TWIScanner

// default destructor
TWIScanner::~TWIScanner()
{
} //~TWIScanner

int TWIScanner::searchDevices()
{
	char buffer[100];
	int findedNode = 0;
	int rtn;
	for(int i =2;i<MAX_TWI_NODE_COUNT;i++)
	{
		
		rtn  = _sequence_start();
		if(rtn == TWI_ERROR_OK)
		{
			;
		}
		rtn = _sequence_address(i,OPRead);
		if(TW_MR_ADDR_ACK == rtn)
		{
			m_searchAddress[findedNode++] = i;
		}
		return findedNode;
	}	
}
int TWIScanner::getDeviceNumber()
{
	return 0;
}
unsigned char TWIScanner::getDeviceAddress(int index)
{
	if(index > MAX_TWI_NODE_COUNT)
		return TWI_DEFAULT_ADDR;
	return m_searchAddress[index];
}