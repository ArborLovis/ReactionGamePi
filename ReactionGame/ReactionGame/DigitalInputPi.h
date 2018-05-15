#pragma once
#include "PinPi.h"
#include "Enums.h"


namespace pi_io
{
	class Digital_input_pi
	{
	public:
		Digital_input_pi(e_pin pin, e_pull_up_down pud, e_edge_type edge, void(*isr_function)(void));
		bool get_digital_input() const;
		
	private:
		e_pin pin_numb_;
	};
}
