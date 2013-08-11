#include <ArduinoStyle.h>

TibuBoard Tibu;
USBSerial Serial;

int main(void)
{
	InitTibuBoard(&Tibu);
	InitUSBSerial(&Serial);
	SystemInit();
	SysTickConfig();
	Init_PWMPins();
	InitADC();
	setup();
    while(1)
    {
    	loop();
    }
}
