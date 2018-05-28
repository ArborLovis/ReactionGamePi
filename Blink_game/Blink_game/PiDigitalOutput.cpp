#include "PiDigitalOutput.h"
#include "PiIoManager.h"

namespace pi_io {

	Pi_digital_output::Pi_digital_output(Pin pin) : pin_{ Pi_io_manager::instance().register_output(pin) }
	{
	}
	
	void Pi_digital_output::set_state(State state)
	{
		Pi_io_manager::instance().digital_write(pin_, state);
	}

	State Pi_digital_output::get_state()
	{
		return Pi_io_manager::instance().digital_read(pin_);
	}

	Pi_digital_output& Pi_digital_output::operator=(State rhs)
	{
		set_state(rhs);
		return *this;
	}

}
