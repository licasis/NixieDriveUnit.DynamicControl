/*
 * Nixie.Dynamic.Drive.6Tube.MK1.cpp
 *
 * Created: 2016-08-20 오전 11:37:40
 * Author : Master
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "Devices/InterDevices.h"
#include "Devices/UART.h"
#include "Devices/TImeTicker.h"
#include "Devices/DynamicTubeDriver.h"
#include "Devices/Driver74141.h"
#include "Devices/BrightControl.h"
#include "Devices/SwitchControl.h"
#include "Objects/ClockTime.h"
#include "Devices/TWIScanner.h"
#include "Devices/DS3231.h"
void Dev_init();
InterDevices *m_pDevices[100]={0};
	
	
ClockTime *m_pclockTime=0;
//TWIScanner *pScanner = 0;
DS3231 *pRealTimeClock=0;
extern volatile unsigned char g_UpdateHOURFlag;
extern volatile unsigned char g_UpdateMINUTEFlag;


int TimerCallback(void *);
int main(void)
{
    /* Replace with your application code */
	
	
    _delay_ms(500); // Wait booting time.
	UART m_uart;
	TimeTicker m_timeTicker;
	DS3231 RealTimeClock;	
	
	
	
	ClockTime m_clockTime;
	DynamicTubeDriver m_dynamicDriver;
	Driver74141 m_driver74141;
	BrightControl m_brightControl;
	SwitchControl m_switchControl;

	pRealTimeClock = & RealTimeClock;
	m_pclockTime = &m_clockTime;	
	m_pDevices[NUM_UART] = &m_uart;
	m_pDevices[NUM_TIMETICKER] = &m_timeTicker;
	m_pDevices[NUM_DYNAMIC_DRIVER] = &m_dynamicDriver;
	m_pDevices[NUM_71414_DRIVER] = &m_driver74141;
	m_pDevices[NUM_BRIGHT_CONTROL_DRIVER] = &m_brightControl;
	m_pDevices[NUM_SWITCH_CONTROL_DRIVER] = &m_switchControl;
	
	_delay_ms(500); // Wait booting time.
	

	//m_pDevices[NUM_SWITCH_CONTROL_DRIVER]->init(0,0,0);
	//while(1);
	int loopCount=0;
	int tempDegree = 3;
	int SwitchState = 0;
	int isMinuteSW_On=0;
	int isHourSW_On=0;
	char buffer[150];
	//_delay_ms(3000);
	Dev_init();
	_delay_ms(500); // Wait booting time.
	RealTimeClock.setAddress(0x68);
	while(0)
	{
		//m_uart.putString("AAAAAAAAAA\r\n");
		m_uart.putString("AAAAAAAAAA");
		_delay_ms(500);
	}

	int readsize =-1;
	unsigned char timeInfo[3];
	int eCode = TWI_ERROR_OK;
	DS3231_Time *pTime=(DS3231_Time *)timeInfo;
	
	m_uart.putString("\r\n\r\n===================================================\r\n");
	m_uart.putString("============  System Clock Start  =================\r\n");
	m_uart.putString("===================================================\r\n");

	
	eCode = RealTimeClock.set1HzOn();
	_delay_ms(100);
	eCode = pRealTimeClock->readRegs(timeInfo , 0,3,&readsize);
	if(eCode == TWI_ERROR_OK)
	{
		m_pclockTime->setTime((pTime->hour20)*20 + (pTime->hour10)*10 + pTime->hour ,(pTime->minute10)*10 + (pTime->minute) ,(pTime->second10)*10 + pTime->second);
		sprintf(buffer,">>from DS3231  :  0x%02x 0x%02x 0x%02x\r\n",timeInfo[0],timeInfo[1],timeInfo[2]);
		m_uart.putString(buffer);
		sprintf(buffer,">>from system  :  %02d:%02d:%02d\r\n",m_pclockTime->getTimeHour(),m_pclockTime->getTimeMinute(),m_pclockTime->getTimeSecond());
		m_uart.putString(buffer);

		
	}
	else
	{
		m_uart.putString("Read Error!!!! \r\n");

		while(1);
		m_pclockTime->setTime(0,0,0);
	}

	
	
	if(eCode != TWI_ERROR_OK)
	{
		;
	}
	m_timeTicker.regCallback(TimerCallback,(void *)&m_clockTime);
	
	_delay_ms(100);
    
	while (1) 
	{

		loopCount++;

		if(loopCount == 0x4F  )
		{

#ifdef USE_INTERRUPT_SW
			if(g_UpdateHOURFlag==2)
			{
				pRealTimeClock->updateHour(m_clockTime.getTimeHour());
				g_UpdateHOURFlag = 0;
			}
				
			if(g_UpdateMINUTEFlag==2)
			{
				pRealTimeClock->updateMinute(m_clockTime.getTimeMinute());
				g_UpdateMINUTEFlag = 0;
			}

#else			
			SwitchState = m_switchControl.getState();
			if(SwitchState & 0x10)
			{
				if(isHourSW_On == 0)
				{
					m_clockTime.hourUp();
					pRealTimeClock->updateHour(m_clockTime.getTimeHour());
				}
				isHourSW_On = 1;
			}
			else
			{
				isHourSW_On = 0;
			}
		
			if(SwitchState & 0x01)
			{
		   		if(isMinuteSW_On == 0 )
		   		{
			   		m_clockTime.minuteUp();
					   pRealTimeClock->updateMinute(m_clockTime.getTimeMinute());
		   		}
				  isMinuteSW_On = 1;
			}
			else
			{
				isMinuteSW_On = 0;
			}
#endif // #ifndef USE_INTERRUPT_SW	
			tempDegree = m_brightControl.getDegree();
			m_dynamicDriver.setBright(tempDegree);
			loopCount = 0;
		}
		m_dynamicDriver.driveNextTube();
    }
}


void Dev_init()
{

	cli();
	
	m_pDevices[NUM_UART]->init(0,0,0);
	m_pDevices[NUM_TIMETICKER]->init(0,0,0);
	m_pDevices[NUM_DYNAMIC_DRIVER]->init(0,0,0);
	m_pDevices[NUM_71414_DRIVER]->init(0,0,0);
	m_pDevices[NUM_BRIGHT_CONTROL_DRIVER]->init(0,0,0);
	m_pDevices[NUM_SWITCH_CONTROL_DRIVER]->init(0,0,0);
	pRealTimeClock->init();
	sei();	
}

int TimerCallback(void *pData)
{
	//char data[100];
	
	((ClockTime *)pData)->FlyTime();
	
	//((UART*)m_pDevices[NUM_UART])->putString("AAA\n");
	//((DynamicTubeDriver *)m_pDevices[NUM_DYNAMIC_DRIVER])->handle();
	//sprintf(data,"TTTT:%02d:%02d:%02d\n",pTime->getTimeHour(),pTime->getTimeMinute(),pTime->getTimeSecond());
	//((UART*)m_pDevices[NUM_UART])->putString("TICK");
	//((UART*)m_pDevices[NUM_UART])->putString(data);
	//((Driver74141 *)m_pDevices[NUM_71414_DRIVER])->setOutput(pTime->getTimeSecond()%10);
	return 0;
}