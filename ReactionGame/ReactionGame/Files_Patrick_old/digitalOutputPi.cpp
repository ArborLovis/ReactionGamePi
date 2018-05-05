#include "digitalOutputPi.h"
#include "pi_gpio_headers.h"
#include <wiringPi.h>

// initialize wiring pi pin 8 as default with value zero
DigitalOutputPi::DigitalOutputPi() : pin_numb_(8), pin_val_(false) // MFA how do you know it is 8?
{
	//wiringPiSetup();
}

// set Pin as default as óutput
DigitalOutputPi::DigitalOutputPi(short const pin_numb, bool const value) : pin_numb_(pin_numb), pin_val_(value)
{
	//wiringPiSetup();
	//pinMode(pin_numb_, OUTPUT);
}

// MFA configuration should be done in the constructor, otherwise your output is not really usable!
void DigitalOutputPi::configDigitalOutput(short const pin_numb, driver_conf driver_strength, output_ctr pin_ctr,
										  pin_mode gpio_mode) // MFA why do you pass the pin_numb again when it is already known from construction? this might cause trouble!
{
	pin_numb_ = pin_numb;

	switch (pin_ctr) // MFA you could just kick this code out for now
	{
	case output_ctr::SOFTWARE_CTR:
		break;
	case output_ctr::HARDWARE_CTR:
		break;
	default:
		break;
	}

	switch (driver_strength)
	{
		case driver_conf::HIGH_STRENGTH:
		break;
		case driver_conf::LOW_STRENGTH:
		break;
	default:
		break;
	}

	switch (gpio_mode)
	{
	case pin_mode::OUT:
		pinMode(pin_numb_, OUTPUT);
		break;
	case pin_mode::PWM_OUT:
		if (pin_numb_ == 1)
			pinMode(pin_numb_, PWM_OUTPUT);
		else
			pinMode(pin_numb_, OUTPUT); // MFA I would not expect that as a user. throw me an exception if I do something that is forbidden!
		break;
	case pin_mode::GPIO_CLK:
		pinMode(pin_numb_, GPIO_CLOCK);
		break;
	default:
		break;
	}

}

void DigitalOutputPi::setDigitalOutput(bool const value)
{
	digitalWrite(pin_numb_, value);
	pin_val_ = value; // MFA you do not need pin_val_, it is only written to here - never read
}

bool DigitalOutputPi::getactDigitalOutput() const
{
	return digitalRead(pin_numb_);
}

void DigitalOutputPi::setPWM(short const pin_numb, int width) // MFA passing pin_numb here again is misleading, use the member variable!
{
	if (width > 100)
		width = 100;
	else if (width < 0)
		width = 0;

	if (pin_numb == 1) // MFA this is not what I expect. again, pin_numb should not be passed as a parameter here!
		pwmWrite(pin_numb, static_cast<int>(width*10.24));
}