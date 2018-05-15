#include "DigitalOutputPi.h"
#include <wiringPi.h>
#include "IoFunctionsPi.h"
#include "Manage_Io.h"

namespace pi_io
{
	Digital_output_pi::Digital_output_pi(Pin pin, Mode mode)
	{
		pin_numb_ = pin;

		Manage_io::register_pin_as_used(pin);

		pinMode(static_cast<int>(pin_numb_), map_mode(mode));
		//std::cout << "All Outputsettings done! Pinnumber = " << static_cast<int> (pin_numb_) << std::endl;
	}
	
	void Digital_output_pi::set(bool value) const
	{
		digitalWrite(static_cast<int>(pin_numb_), value);
		//std::cout << "Digital Output Pin " << static_cast<int>(pin_numb_) << " RESET!" << std::endl;
	}

	bool Digital_output_pi::get() const
	{
		return digitalRead(static_cast<int>(pin_numb_));
	}

}

