/*
 * interDevices.cpp
 *
 * Created: 2016-08-24 오전 2:09:56
 *  Author: Master
 */ 
#include "InterDevices.h"

void InterDevices::regCallback(driverCallback callee,void *pData)
{
	m_pCallbackParam = pData;
	m_callback = callee;
}
