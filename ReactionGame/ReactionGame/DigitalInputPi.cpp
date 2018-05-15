
#include "DigitalInputPi.h"
#include <wiringPi.h>
#include <iostream>
#include "IoFunctionsPi.h"
#include "Manage_Io.h"
#include <stdexcept>


namespace pi_io
{	
	Digital_input_pi::Digital_input_pi(e_pin pin, const e_pull_up_down pud, const e_edge_type edge, void(*isr_function)(void))
	{
		pin_numb_ = pin;

		if (Manage_io::get_io_status(pin))
		{
			throw std::out_of_range("Pin allready in use - Input Error");
			//throw "Error Pin allready in use";
		}			
		else
			Manage_io::register_pin_as_used(pin);

		pinMode(static_cast<int>(pin_numb_), INPUT);
		pullUpDnControl(static_cast<int>(pin_numb_), Io_functions_pi::map_pud(pud));
		wiringPiISR(static_cast<int>(pin_numb_), Io_functions_pi::map_edge(edge), *isr_function);
		//std::cout << "All Inputsettings done! Pinnumber = " << static_cast<int> (pin_numb_) << std::endl;
	}

	bool Digital_input_pi::get_digital_input() const
	{
		return digitalRead(static_cast<int>(pin_numb_));
	}	
}

