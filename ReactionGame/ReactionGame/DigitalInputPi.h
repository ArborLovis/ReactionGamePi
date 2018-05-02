#pragma once
#include "PinPi.h"
#include "Enums.h"
#include "IoFunctionsPi.h"


namespace pi_io
{
	class digital_input_pi
	{
	public:
		digital_input_pi(e_pin pin, e_pull_up_down pud, e_edge_type edge, void(*isr_function)(void));
		bool get_digital_input() const;
		
	private:
		e_pin pin_numb_;
	};
}
