#include <ArduinoStyle.h>

int main(void)
{
	SystemInit();
	SysTickConfig();
	Init_PWMPins();
	setup();
    while(1)
    {
    	loop();
    }
}
