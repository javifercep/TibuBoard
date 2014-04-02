#include "ArduinoStyle.h"


int main(void)
{
	SystemInit();
	SysTickConfig();
	Init_PWMPins();
	InitADC();
	setup();
    while(1)
    {
    	loop();
    	if (serialEventRun) serialEventRun();
    }
}
