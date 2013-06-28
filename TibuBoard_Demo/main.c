#include <ArduinoStyle.h>

int main(void)
{
	SystemInit();
	SysTickConfig();
	setup();
    while(1)
    {
    	loop();
    }
}
