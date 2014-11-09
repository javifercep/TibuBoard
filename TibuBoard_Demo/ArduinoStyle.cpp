#include "ArduinoStyle.h"

#include "SPIAPI.h"

int blinkcounter;

void setup()
{
	blinkcounter = 0;
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	Serial.println("Hello world!");
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  Serial.print(" Number of blinks: ");
  Serial.println(blinkcounter++);

}


