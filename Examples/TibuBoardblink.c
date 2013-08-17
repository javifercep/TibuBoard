#include "ArduinoStyle.h"

void setup() {
	Tibu.InitLED(LED1);
}

void loop() {
	Tibu.ToggleLED(LED1);
	delay(1000);
}