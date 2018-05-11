#include "Manage_Io.h"
#include <cstring>
#include <iostream>
#include "IoFunctionsPi.h"

int pi_io::Manage_io::io_list_[28];

pi_io::Manage_io::Manage_io()
{
	for (auto& i : io_list_)	//initialize array
		i = 0;
}

void pi_io::Manage_io::set_io_input(e_pin pin)
{
	io_list_[Io_functions_pi::map_pin(pin)] = 1;
	//std::cout << "New IO set to: bcm_" << Io_functions_pi::map_pin(pin) << std::endl;
}

bool pi_io::Manage_io::get_io_status(e_pin pin)
{	
	//std::cout << "Status checked of IO: bcm_" << Io_functions_pi::map_pin(pin) << " = " << io_list_[Io_functions_pi::map_pin(pin)] << std::endl;
	return io_list_[Io_functions_pi::map_pin(pin)];
}

void pi_io::Manage_io::get_overall_status()
{
	for (auto i = 0; i < (sizeof(io_list_) / sizeof(*io_list_)); i++)
	{
		std::cout << "bcm_" << i << " = "; if (io_list_[i]) std::cout << "TRUE" << std::endl; else std::cout << "FALSE" << std::endl;
	}	
}
