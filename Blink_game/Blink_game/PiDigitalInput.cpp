#include "PiDigitalInput.h"
#include "PiIoManager.h"

namespace pi_io {

	Pi_digital_input::Pi_digital_input(Pin pin, Pull_up_down pud, Edge_type edge,
		std::function<void(Pin)> value_change_handler) :
		pin_{ Pi_io_manager::instance().register_input(pin, value_change_handler, pud, edge) }
	{
	}

	State Pi_digital_input::read() const
	{
		auto const val = Pi_io_manager::instance().digital_read(pin_);
		return State(val);
	}

}