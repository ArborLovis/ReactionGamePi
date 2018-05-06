#include "Manage_Io.h"
#include <cstring>
#include <iostream>

int pi_io::Manage_io::io_list_[32];

pi_io::Manage_io::Manage_io()
{
	for (auto& i : io_list_)
		i = 0;
}

void pi_io::Manage_io::set_io_input(e_pin pin)
{
	io_list_[static_cast<char> (pin)] = 1;
	std::cout << "New IO set to: " << static_cast<int>(pin) << std::endl;
}

bool pi_io::Manage_io::get_io_status(e_pin pin)
{	
	std::cout << "Status checked of IO: " << static_cast<int>(pin) << " = " << io_list_[static_cast<char>(pin)] << std::endl;
	return io_list_[static_cast<char>(pin)];
}

void pi_io::Manage_io::get_overall_status()
{
	for (auto i = 0; i < 32; i++)
		std::cout << "bcm_" << i << " = " << io_list_[i] << std::endl;
}
