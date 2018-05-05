#pragma once

#include "pi_gpio_headers.h"

class IDigitalInput // MFA naming -> IDigital_input
{
public:			
	// MFA method naming! also config() method is probably too implementation specific, should be handled by constructor
	virtual void configDigitalInput(short const pin_numb, pud_conf const pud_setting) = 0;	// selection, if controlled by interrupt or polling
	virtual void configInputAsInterrupt(short const pin_numb, trig_setup const int_conf, void(*pIntHandler)(void)) = 0;	// select interrupt trigger
	virtual bool getDigitalInput() const = 0;						// actual digital input value
	virtual ~IDigitalInput() = 0;
};
