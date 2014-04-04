#include "ArduinoStyle.h"

Tibuboard Tibu;

void setup() {
	 pinMode(pushButton, INPUT);
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