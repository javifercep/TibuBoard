#include "ArduinoStyle.h"

#include "SPIAPI.h"

const int NSS = 10;
const int CE = 8;
const int IRQ = 9;
Tibuboard Tibu;

void setup()
{
	SPI.begin(SPI_MASTER);
	Serial.begin(115200);
	Tibu.LEDOff(LED1);
	Tibu.LEDOn(LED2);
	Serial.println("Hola");
	pinMode(NSS,OUTPUT);
	pinMode(CE,OUTPUT);
	pinMode(IRQ, INPUT);
	digitalWrite(NSS,HIGH);
	digitalWrite(CE,LOW);
	delay(10000);
	digitalWrite(NSS,LOW);
	Serial.println(SPI.transfer(0x00));
	Serial.println(SPI.transfer(0xFF));
	digitalWrite(NSS,HIGH);
	Tibu.LEDOn(LED1);
}

void loop()
{
	Serial.println("Hola");
	delay(500);

}


