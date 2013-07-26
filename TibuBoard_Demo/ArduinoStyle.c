#include "ArduinoStyle.h"

TibuBoard Tibu;
uint32_t On=0, fade=0;



void blink(void)
{
	Tibu.ToggleLED(LED1);
}

void setup()
{
	int jj;

	InitTibuBoard(&Tibu);
	Tibu.InitAllLED();
	Tibu.InitAllButton();
	Tibu.InitButton(USER_BUTTON3);
	Tibu.ButtonInterrupt(USER_BUTTON3,blink);
	for(jj=1; jj< 20; jj++)pinMode(jj,OUTPUT);
	pinMode(0,INPUT);
}

void loop()
{
	uint32_t ii;

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
	analogWrite(3, fade+=1000);
	if(fade==65000)fade=0;
	On=On^1;
	delay(100);

}


