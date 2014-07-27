#include "ArduinoStyle.h"
#include "InterruptManager.h"

int main(void)
{
	SystemInit();
	SysTickConfig();
	InitInterruptManager();
	Init_PWMPins();
	InitADC();
	setup();
    while(1)
    {
    	loop();
    	if (serialEventRun) serialEventRun();
    }
}
