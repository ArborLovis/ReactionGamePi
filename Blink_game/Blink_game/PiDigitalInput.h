#pragma once

#include "Pin.h"
#include "PinHandle.h"
#include "Enums.h"

#include <functional>

namespace pi_io {

	class Pi_digital_input
	{
	public:
		Pi_digital_input(Pin pin, Pull_up_down pud = Pull_up_down::up, Edge_type edge = Edge_type::rising,
			std::function<void(Pin)> value_change_handler = nullptr);

		State read() const;

		Pi_digital_input(const Pi_digital_input& other) = delete;
		Pi_digital_input(Pi_digital_input&& other) = default;
		Pi_digital_input& operator=(const Pi_digital_input &rhs) = delete;
		Pi_digital_input& operator=(Pi_digital_input &&rhs) = default;
		~Pi_digital_input() = default;

	private:
		Pin_handle pin_;
	};

}
