#include "ArduinoStyle.h"


uint32_t On=0, fade=0;



void blink(void)
{
	Tibu.ToggleLED(LED1);
}

void setup()
{
	int jj;

	Serial.begin();
	Tibu.InitAllLED();
	Tibu.InitAllButton();
	Tibu.InitButton(USER_BUTTON3);
	Tibu.ButtonInterrupt(USER_BUTTON3,blink);
	for(jj=1; jj< 20; jj++)
		if(jj!=A3)pinMode(jj,OUTPUT);
	pinMode(0,INPUT);
}


void loop()
{
	uint32_t ii;
	uint16_t pwm;
	char *toprint;
	toprint = malloc(sizeof(char)*100);

	if(!Tibu.GetStateButton(USER_BUTTON4))Tibu.LEDOn(LED2);
	else Tibu.LEDOff(LED2);

	if(digitalRead(0))Tibu.LEDOn(LED3);
	else Tibu.LEDOff(LED3);

	Tibu.ToggleLED(LED4);
	for(ii=1; ii<20; ii++)
	{
		if(ii!=3)
		{
			if(On)
				digitalWrite(ii,HIGH);
			else
				digitalWrite(ii,LOW);
		}
	}
	pwm=mapInt16(analogRead(),0, 1023,0,MAXPWMPERIOD);
	Serial.println("Hello!");
	analogWrite(3,pwm);
	On=On^1;
	delay(1000);
	if(Serial.available()>0)
	{
		toprint =(char*) Serial.readUntil('\n');
		Serial.print((const char *)toprint);
	}

}


