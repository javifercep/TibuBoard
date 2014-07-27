#include "ArduinoStyle.h"

Tibuboard Tibu;

void blink()
{
	Tibu.LEDToggle(LED1);
}

void blink2()
{
	Tibu.LEDToggle(LED2);
}


void setup()
{
	Tibu.ButtonInterrupt(USER_BUTTON1, blink);
	Tibu.ButtonInterrupt(USER_BUTTON1, blink2);
}

void loop()
{

}


