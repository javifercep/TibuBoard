#include "ArduinoStyle.h"

TibuBoard Tibu;

void blink(void)
{
	Tibu.ToggleLED(LED1);
}

void setup()
{
	InitTibuBoard(&Tibu);
	Tibu.InitAllLED();
	Tibu.InitAllButton();
	Tibu.ButtonInterrupt(USER_BUTTON1,blink);
}

void loop()
{
	if(!Tibu.GetStateButton(USER_BUTTON3))Tibu.LEDOn(LED2);
	else Tibu.LEDOff(LED2);

	Tibu.ToggleLED(LED4);
	delay(1000);

}


