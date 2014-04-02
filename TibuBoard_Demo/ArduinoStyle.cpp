#include "ArduinoStyle.h"


uint32_t On=0, fade=0;

Tibuboard Tibu;
String message = String ("Hello!");

void blink(void)
{
	Tibu.LEDToggle(LED1);
}

void setup()
{
	int jj;

	Serial.begin(9600);
	Tibu.ButtonInterrupt(USER_BUTTON3,blink);
	for(jj=1; jj< 20; jj++)
		if(jj!=A3)pinMode(jj,OUTPUT);
	pinMode(0,INPUT);
}


void loop()
{
	uint32_t ii;
	uint16_t pwm;
	char toprint;

	if(!Tibu.GetStateButton(USER_BUTTON4))Tibu.LEDOn(LED2);
	else Tibu.LEDOff(LED2);

	if(digitalRead(0))Tibu.LEDOn(LED3);
	else Tibu.LEDOff(LED3);

	Tibu.LEDToggle(LED4);
	pwm=mapInt16(analogRead(),0, 1023,0,MAXPWMPERIOD);
	Serial.println("Hello!");
	analogWrite(3,pwm);
	delay(1000);
	if(Serial.available()>0)
	{
		toprint = Serial.read();
		Serial.print(toprint);
	}

}


