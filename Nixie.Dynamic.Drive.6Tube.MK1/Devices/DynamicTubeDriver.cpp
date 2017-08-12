/* 
* DynamicTubeDriver.cpp
*
* Created: 2016-08-26 오전 1:46:11
* Author: Master
*/


#include "DynamicTubeDriver.h"
#include "UART.h"
#include "../Objects/ClockTime.h"
#include "Driver74141.h"
extern ClockTime *m_pclockTime;
// default constructor
DynamicTubeDriver::DynamicTubeDriver()
{
	m_currentTube = 0;
	m_brightDegree=MAX_BRIGHT_DEGREE;
	m_flagOnOff=TUBE_DRIVER_ON;
	
	//for(int i=0;i<TUBE_COUNT;i++)
		m_tube[0]=1<<0;
		m_tube[1]=1<<1;
		m_tube[2]=1<<2;
		m_tube[3]=1<<3;
		m_tube[4]=1<<5;
		m_tube[5]=1<<4;
		
		
} //DynamicTubeDriver

// default destructor
DynamicTubeDriver::~DynamicTubeDriver()
{
} //~DynamicTubeDriver
void DynamicTubeDriver::operator delete(void * p) // or delete(void *, std::size_t)
{
	//std::free(p);
}
void DynamicTubeDriver::init(void *param1,void *param2,void *param3)
{
	unsigned char temp=0;
	for(int i=0;i<TUBE_COUNT;i++)
	{
		temp = (temp<<1) | 1; 
	}
	IO_DDR_FOR_DYNAMIC_SWITCH = temp;
	IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
}
void DynamicTubeDriver::driveNextTube()
{
	char drive_value=0xff;
	enum durationLevel{Level0,Level1,Level2,Level3,Level4,Level5,Level6,Level7,Level8,Level9};
		
	//enum durationOn{LvOn0=500,LvOn1=1000,LvOn2=1500,LvOn3=2000,LvOn4=2500,LvOn5=3000,LvOn6=3500,LvOn7=4000,LvOn8=4500,LvOn9=5000};
	//enum durationOff{LvOff0=5000,LvOff1=4500,LvOff2=4000,LvOff3=3500,LvOff4=3000,LvOff5=2500,LvOff6=2000,LvOff7=1500,LvOff8=1000,LvOff9=500};
		
	enum durationOn{	LvOn0=300,		LvOn1=600,		LvOn2=900,		LvOn3=1200,		LvOn4=1500,		LvOn5=1800,		LvOn6=2100,		LvOn7=2400,	LvOn8=2700,		LvOn9=3000	};
	enum durationOff{	LvOff0=3000,	LvOff1=2700,	LvOff2=2400,	LvOff3=2100,	LvOff4=1800,	LvOff5=1500,	LvOff6=1200,	LvOff7=900,	LvOff8=600,		LvOff9=300	};
						
	//enum durationOn{LvOn0=1,LvOn1=2,LvOn2=3,LvOn3=4,LvOn4=5,LvOn5=6,LvOn6=7,LvOn7=8,LvOn8=9,LvOn9=10};
	//enum durationOff{LvOff0=10,LvOff1=9,LvOff2=8,LvOff3=7,LvOff4=6,LvOff5=5,LvOff6=4,LvOff7=3,LvOff8=2,LvOff9=1};	
#if 0
		if(m_flagOnOff == TUBE_DRIVER_OFF)
		{
#ifdef _UART_LOG	
			{
				((UART*)m_pDevices[NUM_UART])->putString("Tube drive off");
			}
#endif
			IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
			_delay_us(LvOff0);	
			_delay_us(LvOn0);	
			return;		
		}
#endif
		//
		
#ifdef _UART_LOG		
		{
			char buffer[100];
			sprintf(buffer,"TUBE = 0x%x , bright = %d \n", m_tube[m_currentTube],m_brightDegree);
			((UART*)m_pDevices[NUM_UART])->putString(buffer);
		}
#endif
		
		
	
		
		
		IO_PORT_FOR_DYNAMIC_SWITCH = m_tube[m_currentTube] ;
		
#if 0
		_delay_us(10000); 
		IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
		
#else

		switch(m_brightDegree)
		{
			case Level0:
				_delay_us(LvOn0); 	
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff0); 
				break;
			case Level1:
				_delay_us(LvOn1); 	
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff1);
				break;
			case Level2:
				_delay_us(LvOn2); 	
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff2);
				break;
			case Level3:
				_delay_us(LvOn3); 	
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff3);
				break;
			case Level4:
				_delay_us(LvOn4); 	
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff4);
				break;
			case Level5:
				_delay_us(LvOn5);
				IO_PORT_FOR_DYNAMIC_SWITCH =  0x00;
				_delay_us(LvOff5);
				break;
			case Level6:
				_delay_us(LvOn6);
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff6);
				break;
			
			case Level7:
				_delay_us(LvOn7);
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff7);
				break;
			
			case Level8:
				_delay_us(LvOn8);
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff8);
				break;
			
			case Level9:
				_delay_us(LvOn9);
				IO_PORT_FOR_DYNAMIC_SWITCH = 0x00;
				_delay_us(LvOff9);
				//_delay_us(LvOff9);
				break;
					
		}
#endif
		m_currentTube++;
#if 1
		if(!(m_currentTube ^ 6))
			m_currentTube = 0;
#else
		if(m_currentTube== 6)
		m_currentTube = 0;
#endif				
		// Setup next tube here , because Tube was turned off and had cooling time at least 300ns  already. So, it don't need any cooltime anymore 
		switch(m_currentTube)
		{
			case 0:
				drive_value = m_pclockTime->getTimeHour()/10;
				break;
			case 1:
				drive_value =	m_pclockTime->getTimeHour()%10;
				break;
			case 2:
				drive_value = m_pclockTime->getTimeMinute()/10;
				break;
			case 3:
				drive_value = (m_pclockTime->getTimeMinute())%10;
				break;
			case 4:
				drive_value = m_pclockTime->getTimeSecond()/10;
				break;
			case 5:
				drive_value = (m_pclockTime->getTimeSecond() )%10;
				break;
				
		}	
		//((UART*)m_pDevices[NUM_UART])->putChar((drive_value+'0'));
		//((UART*)m_pDevices[NUM_UART])->putChar(('\n'));
		((Driver74141 *)m_pDevices[NUM_71414_DRIVER])->setOutput(drive_value);
		_delay_us(DELAY_NS_FOR_TUBE_DRIVE);

		 //= (m_currentTube+1)%(TUBE_COUNT);
		
		
}
void DynamicTubeDriver::handle()
{
		driveNextTube();
}

int DynamicTubeDriver::setBright(int value )
{
	if(value >= MAX_BRIGHT_DEGREE )
		m_brightDegree = MAX_BRIGHT_DEGREE;
	else if(value <= MIN_BRIGHT_DEGREE )
		m_brightDegree = MIN_BRIGHT_DEGREE;
	else
		m_brightDegree = value;
	return m_brightDegree;
		
}