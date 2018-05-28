#pragma once

#include "Pin.h"
#include "PinHandle.h"
#include "Enums.h"

namespace pi_io {

	class Pi_digital_output
	{
	public:
		Pi_digital_output(Pin pin);

		void set_state(State state);
		State get_state();

		Pi_digital_output(const Pi_digital_output& other) = delete;
		Pi_digital_output(Pi_digital_output&& other) = default;
		Pi_digital_output& operator=(const Pi_digital_output &rhs) = delete;
		Pi_digital_output& operator=(Pi_digital_output &&rhs) = default;
		~Pi_digital_output() = default;

		Pi_digital_output& operator=(State rhs);

	private:
		Pin_handle pin_;
	};

}
