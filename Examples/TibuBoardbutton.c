#include "ArduinoStyle.h"

void setup() {
	 Tibu.InitButton(USER_BUTTON1);
	 Tibu.InitLED(LED1);
}

void loop() {
	 int buttonState;
	 buttonState = Tibu.GetStateButton(USER_BUTTON1);
	 if(buttonState == HIGH)
	   Tibu.LEDOn(LED1);
	 else
	   Tibu.LEDOff(LED1);
	 delay(100); 
}