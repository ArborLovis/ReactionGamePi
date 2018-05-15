#pragma once
#include "PinPi.h"
#include "Enums.h"


namespace pi_io
{
	class Digital_output_pi
	{
	public:
		Digital_output_pi(Pin pin, Mode mode);
		void set(bool value) const;
		bool get() const;

	private:
		Pin pin_numb_;

	};
}
