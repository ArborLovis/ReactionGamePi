#pragma once
#include "PinPi.h"
#include "Enums.h"


namespace pi_io
{
	class Digital_output_pi
	{
	public:
		Digital_output_pi(e_pin pin, e_mode mode);
		void set(bool value) const;
		bool get() const;

	private:
		e_pin pin_numb_;

	};
}
