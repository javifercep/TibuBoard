#include "ArduinoStyle.h"

#include "SPIAPI.h"

Tibuboard Tibu;

void blink (void);

void setup() {

	Tibu.ButtonInterrupt(USER_BUTTON1,blink);
}

void loop() {

}

void blink()
{
	Tibu.LEDToggle(LED1);
}


