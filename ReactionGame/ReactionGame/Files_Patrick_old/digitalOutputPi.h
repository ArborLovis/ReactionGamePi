#pragma once
#include "IDigitalOutput.h"
#include "pi_gpio_headers.h"


class DigitalOutputPi final : public IDigitalOutput
{
public:
	DigitalOutputPi();
	// MFA pin_numb is already passed here
	DigitalOutputPi(short const pin_numb, bool const value); // MFA const can be ommitted when passing by value in headers
	// MFA and again here
	void configDigitalOutput(short const pin_numb, driver_conf const driver_strength, output_ctr const pin_ctr,
							 pin_mode gpio_mode) override;
	void setDigitalOutput(bool const value) override;
	bool getactDigitalOutput() const override;
	// MFA and again here - this will cause trouble!
	void setPWM(short const pin_numb, int width);

private:
	short pin_numb_;
	bool pin_val_; // MFA pin_val never used
};




