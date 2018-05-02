#pragma once
#include "PinPi.h"
#include "Enums.h"

#include "IoFunctionsPi.h"


namespace pi_io
{
	class digital_output_pi
	{
	public:
		digital_output_pi(e_pin pin, e_mode mode);
		void set_digital_output_true() const;
		void set_digital_output_false() const;
		bool get_digital_output() const;




	private:
		e_pin pin_numb_;

	};
}
