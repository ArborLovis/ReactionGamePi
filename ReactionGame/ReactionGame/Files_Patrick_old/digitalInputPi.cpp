#include "digitalInputPi.h"
#include "pi_gpio_headers.h"
#include <wiringPi.h>

DigitalInputPi::DigitalInputPi() : pin_numb_(8) // MFA how do you know it is 8? delete the default ctor in this case!
{
	wiringPiSetup();	//maps pin numbers to wiring numbers
}

DigitalInputPi::DigitalInputPi(short const pin_numb) : pin_numb_(pin_numb)
{
	wiringPiSetup(); // MFA will be called pretty often!
	pinMode(pin_numb_, INPUT);
}

void DigitalInputPi::configDigitalInput(short const pin_numb, pud_conf const pud_setting)
{
	pin_numb_ = pin_numb; // MFA you may change the pin-numb, but you do not call pinMode again.

	switch (pud_setting)
	{ // MFA you could map your pud_conf to PUD_-defines from wiringPi.h and reduce the code below to 1 line

	case pud_conf::NONE:
		pullUpDnControl(pin_numb_, PUD_OFF);
		break;
	case pud_conf::PULL_DOWN:
		pullUpDnControl(pin_numb_, PUD_DOWN);
		break;
	case pud_conf::PULL_UP:
		pullUpDnControl(pin_numb_, PUD_UP);
		break;
	default:
		pullUpDnControl(pin_numb_, PUD_OFF);
		break;
	}

}

void DigitalInputPi::configInputAsInterrupt(short const pin_numb, trig_setup const int_conf, void(*pIntHandler)(void))
{
	int dummy = 0;

	if (pin_numb == pin_numb_)
	{
		switch (int_conf)
		{ // MFA you could map your trig_setup to the #define'd values from wiringPi.h, this would reduce your code size
		case trig_setup::SENSE_RISING_EDGE:
			wiringPiISR(pin_numb_, INT_EDGE_RISING, *pIntHandler);
			break;
		case trig_setup::SENSE_FALLING_EDGE:
			wiringPiISR(pin_numb_, INT_EDGE_FALLING, *pIntHandler);
			break;
		case trig_setup::SENSE_BOTH_EDGES:
			wiringPiISR(pin_numb_, INT_EDGE_BOTH, *pIntHandler);
			break;
		case trig_setup::SENSE_EDGE_SETUP:
			wiringPiISR(pin_numb_, INT_EDGE_BOTH, *pIntHandler);
				break;
		default:
			break;
		}
	}
	else
	{ // MFA you should not handle this differently from configDigitalInput. I mean, you should not pass the pin-number at all - but if, it should be handled consistently.
		//error, false pin number --> pin has to be configured first
	}
}

bool DigitalInputPi::getDigitalInput() const
{
	return digitalRead(pin_numb_);
}


