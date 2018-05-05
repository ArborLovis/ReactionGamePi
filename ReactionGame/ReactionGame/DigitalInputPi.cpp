
#include "DigitalInputPi.h"
#include <wiringPi.h>
#include <iostream>
#include "IoFunctionsPi.h"


namespace pi_io
{
	pi_io::Digital_input_pi::Digital_input_pi(e_pin pin, const e_pull_up_down pud, const e_edge_type edge, void(*isr_function)(void))
	{
		pin_numb_ = pin;

		pinMode(static_cast<int>(pin_numb_), INPUT);
		pullUpDnControl(static_cast<int>(pin_numb_), pi_io::Io_functions_pi::map_pud(pud));
		wiringPiISR(static_cast<int>(pin_numb_), pi_io::Io_functions_pi::map_edge(edge), *isr_function);
		//std::cout << "All Inputsettings done! Pinnumber = " << static_cast<int> (pin_numb_) << std::endl;
	}

	bool pi_io::Digital_input_pi::get_digital_input() const
	{
		return digitalRead(static_cast<int>(pin_numb_));
	}	
}

