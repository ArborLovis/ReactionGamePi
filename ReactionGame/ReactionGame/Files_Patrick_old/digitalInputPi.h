#pragma once

#include "IDigitalInput.h"
#include "pi_gpio_headers.h"

class DigitalInputPi final : public IDigitalInput
{
public:
	DigitalInputPi(); // MFA no default ctor, does not make sense here!
	// MFA you pass your pin numb here
	DigitalInputPi(short const pin_numb);
	// MFA and here
	void configDigitalInput(short const pin_numb, pud_conf const pud_setting) override;	// MFA const not needed in headers for values
	// MFA ... and here... once, in the constructor, should be enough
	void configInputAsInterrupt(short const pin_numb, trig_setup const int_conf, void(*pIntHandler)(void)) override;
	bool getDigitalInput() const override;	

private:
	short pin_numb_;

};
