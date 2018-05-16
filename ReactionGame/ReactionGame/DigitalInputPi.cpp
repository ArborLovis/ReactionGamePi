
#include "DigitalInputPi.h"
#include "piproxy.h"
#include <iostream>
#include "IoFunctionsPi.h"
#include "Manage_Io.h"
#include <stdexcept>
#include <exception>


namespace pi_io
{	
	Digital_input_pi::Digital_input_pi(Pin pin, const Pull_up_down pud, const Edge_type edge, void(*isr_function)(void))
	{
		pin_numb_ = pin;

		Manage_io::register_pin_as_used(pin);

		pinMode(static_cast<int>(pin_numb_), INPUT);
		pullUpDnControl(static_cast<int>(pin_numb_), map_pud(pud));
		wiringPiISR(static_cast<int>(pin_numb_), map_edge(edge), *isr_function);
		//std::cout << "All Inputsettings done! Pinnumber = " << static_cast<int> (pin_numb_) << std::endl;
	}

	bool pi_io::Digital_input_pi::get_digital_input() const
	{
		return digitalRead(static_cast<int>(pin_numb_));
	}	
}

