#include "Manage_Io.h"
#include <iostream>
#include "IoFunctionsPi.h"

namespace pi_io {

	std::array<int, Manage_io::pin_numbers_> Manage_io::io_list_{ 0 };

	Manage_io::Manage_io()
	{
		//for (auto& i : io_list_)	//initialize array
		// i = 0;
		unsigned short i = 0;
		while (i < pin_numbers_)
		{
			io_list_[i++] = 0;
		}
	}

	void Manage_io::register_pin_as_used(Pin pin)
	{
		request_pin(map_pin(pin));
		//std::cout << "New IO set to: bcm_" << Io_functions_pi::map_pin(pin) << std::endl;
	}

	void Manage_io::get_overall_status()
	{
		for (auto i = 0; i < pin_numbers_; i++)
		{
			std::cout << "bcm_" << i << " = ";
			if (io_list_[i])
				std::cout << "TRUE" << std::endl;
			else
				std::cout << "FALSE" << std::endl;
		}
	}

	void Manage_io::request_pin(const int desired_pin)
	{
		if (desired_pin < pin_numbers_)
		{
			if (io_list_[desired_pin] == 0)
			{
				io_list_[desired_pin] = 1;
			}
			else
			{
				throw std::logic_error("Pin is allready in use!");
			}
		}
		else
			throw std::length_error("Pin Nr. does not exist!");
	}
}