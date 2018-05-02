#include "DigitalOutputPi.h"
#include <wiringPi.h>
#include <iostream>
#include "IoFunctionsPi.h"


namespace pi_io
{
	pi_io::digital_output_pi::digital_output_pi(e_pin pin, e_mode mode)
	{
		pin_numb_ = pin;

		pinMode(static_cast<int>(pin_numb_), pi_io::io_functions_pi::map_mode(mode));
		//std::cout << "All Outputsettings done! Pinnumber = " << static_cast<int> (pin_numb_) << std::endl;
	}

	void pi_io::digital_output_pi::set_digital_output_true() const
	{
		digitalWrite(static_cast<int>(pin_numb_), TRUE);
		//std::cout << "Digital Output Pin " << static_cast<int>(pin_numb_) << " SET!" << std::endl;
	}

	void pi_io::digital_output_pi::set_digital_output_false() const
	{
		digitalWrite(static_cast<int>(pin_numb_), FALSE);
		//std::cout << "Digital Output Pin " << static_cast<int>(pin_numb_) << " RESET!" << std::endl;
	}

	bool pi_io::digital_output_pi::get_digital_output() const
	{
		return digitalRead(static_cast<int>(pin_numb_));
	}

}

