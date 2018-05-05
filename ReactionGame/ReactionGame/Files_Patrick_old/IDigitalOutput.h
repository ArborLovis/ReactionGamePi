#pragma once

#include "pi_gpio_headers.h"

class IDigitalOutput
{
public:
	// MFA I would kick this method out. it is probably implementation specific. should be handled by constructor
	virtual void configDigitalOutput(short const pin_numb, driver_conf const driver_strength, output_ctr const pin_ctr,
									 pin_mode gpio_mode) = 0;		// selection of driving strength and multiplexed pins. 
	virtual void setDigitalOutput(bool const value) = 0;			// set digital output to a value
	virtual bool getactDigitalOutput() const = 0;			// get value, which is allready written to the pin

	virtual ~IDigitalOutput() = 0;
};