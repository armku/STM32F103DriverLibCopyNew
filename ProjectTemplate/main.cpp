#include "stm32f10x.h"

/***** System *****/
#include "Configuration.h"
#include "TaskManager.h"

/***** OnChip *****/
#include "USART.h"
#include "I2C.h"
//#include "Timer.h"
#include "ADC.h"
#include "PWM.h"
#include "InputCapture_TIM.h"
#include "InputCapture_EXIT.h"

/***** OffChip*****/
#include "StepMotor.h"
#include "MPU6050.h"
#include "Gimbal.h"
//#include "AHRS.h"
#include "Ultrasonic.h"
#include "Remoter_PWM_TIM.h"
#include "Remoter_PWM_EXIT.h"
#include "LED.h"
#include "Socket_esp8266.h"

/***** ToolBox*****/
#include "Mathtool.h"
#include "GidLink.h"

/********IAP Bootloader**************/
//#define IAPBOOTLOADRT
//#ifdef IAPBOOTLOADRT
//SCB->VTOR = FLASH_BASE | 0x8000;
//#endif

union DataConvert
{
	int byInt;
	float byFloat;
	u8  byByte[4];
} dataConvert;

union DoubleDataConvert
{
	double byDouble;
	u8  byByte[8];
} doubledataConvert;


//////////////////////////////////////////////////////////////////////////////
//////////////////            Global Variable       //////////////////////////
//////////////////////////////////////////////////////////////////////////////

int main()
{
	uint16_t loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt=0;
	while (tskmgr.Time() < 1);

	double curTime = 0, oldTime = 0;
	int cnt = 0;

	while (1)
	{
		curTime = tskmgr.Time();
		float deltaT = curTime - oldTime;

		if (deltaT >= 0.002)
		{
				oldTime = curTime;
			
			loop500Hzcnt++;
			if(loop500Hzcnt>=5)
			{//100HZ 控制
				loop500Hzcnt = 0;
				loop100HzCnt++;
				if(loop100HzCnt>=2)
				{//50HZ 
					loop100HzCnt=0;
					loop10HzCnt++;
					if(loop10HzCnt>=5)
					{//10HZ
						loop10HzCnt=0;
					}
				}
			}

			if (++cnt > 5)
			{
				cnt = 0;
//				com<<"test"<<"\r\n";
			}
		}
	}
}
