#pragma once
#include "PinPi.h"

namespace pi_io
{
	class Manage_io
	{
	public:
		Manage_io();
		static void set_io_input(e_pin pin);
		static bool get_io_status(e_pin pin);
		static void get_overall_status();

	private:
		static int io_list_[28];
		//static int test;
	};
}

