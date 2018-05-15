#pragma once
#include "PinPi.h"
#include "Enums.h"


namespace pi_io
{
	class Digital_input_pi
	{
	public:
		Digital_input_pi(Pin pin, Pull_up_down pud, Edge_type edge, void(*isr_function)(void));
		bool get_digital_input() const;
		
	private:
		Pin pin_numb_;
	};
}
