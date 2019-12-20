// sifflet.ino

#include "PinChangeInterrupt.h"

#define PIN_LED 9
#define PIN_CTRL 13
#define PIN_LORA_RESET 5
#define PIN_LORA_NSS 6
#define PIN_LORA_DIO0 2
#define PIN_LORA_DIO1 3
#define PIN_LORA_DIO2 4
#define PIN_BUTTON A0

void setup(){

	// Setup button
	pinMode(PIN_BUTTON, INPUT_PULLUP);
	attachPCINT(digitalPinToPCINT(PIN_BUTTON), interruptButton, CHANGE);

	// Setup sleep
	// require the use of MiniCore from MCUdude to work
	
	sleepMode(SLEEP_POWER_DOWN);
	disablePower(POWER_ADC);
	disablePower(POWER_SPI);
	disablePower(POWER_TIMER1);
	disablePower(POWER_TIMER2);
	disablePower(POWER_TIMER3);
	disablePower(POWER_SERIAL0);
	disablePower(POWER_SERIAL1);

	// Setup outputs
	pinMode(PIN_CTRL, OUTPUT);
	digitalWrite(PIN_CTRL, HIGH);
	delay(1000);
	digitalWrite(PIN_CTRL, LOW);

	enterSleep();
}

void interruptButton(){
	digitalWrite(PIN_CTRL, !digitalRead(PIN_CTRL));
}

void loop(){
}

void enterSleep(){
	sleep();
}