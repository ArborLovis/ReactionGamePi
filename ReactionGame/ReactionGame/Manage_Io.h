#pragma once
#include "PinPi.h"
#include <array>

namespace pi_io
{
	class Manage_io
	{
	public:
		Manage_io();
		static void register_pin_as_used(Pin pin);
		static void get_overall_status();

		static void request_pin(int desired_pin);

	private:
		static constexpr int pin_numbers_ = 32;
		static std::array<int, pin_numbers_> io_list_;
	};
}

