#include "ArduinoStyle.h"

Tibuboard Tibu;

void setup()
{

}

void loop()
{
	int buttonState;
	buttonState = Tibu.GetStateButton(USER_BUTTON1);
	if(buttonState == HIGH)
		Tibu.LEDOn(LED1);
	else
		Tibu.LEDOff(LED1);
	delay(100);

}