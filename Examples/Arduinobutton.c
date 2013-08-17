#include "ArduinoStyle.h"

void setup() {
	 pinMode(pushButton, INPUT);
	 Tibu.InitLED(LED1);
}

void loop() {
	 int buttonState;
	 buttonState = digitalRead(pushButton);
	 if(buttonState == HIGH)
	   Tibu.LEDOn(LED1);
	 else
	   Tibu.LEDOff(LED1);
	 delay(100); 
}