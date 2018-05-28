#include "PiIoManager.h"

#include "piproxy.h"
#include "PinHandle.h"

#include <memory>
#include <sstream>

namespace pi_io {

	Pi_io_manager::Pi_io_manager()
	{
		setup_interrupt_handlers();
		for (auto i = 0; i < io_count; i++)
		{
			ios_[i] = false;
		}

		setup_wiring_pi();
	}

	void Pi_io_manager::setup_interrupt_handlers()
	{ // we need distinct error handlers for each io port
		interrupt_handlers_[0] = []() { forward_interrupt(Pin::bcm_0); };
		interrupt_handlers_[1] = []() { forward_interrupt(Pin::bcm_1); };
		interrupt_handlers_[2] = []() { forward_interrupt(Pin::bcm_2); };
		interrupt_handlers_[3] = []() { forward_interrupt(Pin::bcm_3); };
		interrupt_handlers_[4] = []() { forward_interrupt(Pin::bcm_4); };
		interrupt_handlers_[5] = []() { forward_interrupt(Pin::bcm_5); };
		interrupt_handlers_[6] = []() { forward_interrupt(Pin::bcm_6); };
		interrupt_handlers_[7] = []() { forward_interrupt(Pin::bcm_7); };
		interrupt_handlers_[8] = []() { forward_interrupt(Pin::bcm_8); };
		interrupt_handlers_[9] = []() { forward_interrupt(Pin::bcm_9); };
		interrupt_handlers_[10] = []() { forward_interrupt(Pin::bcm_10); };
		interrupt_handlers_[11] = []() { forward_interrupt(Pin::bcm_11); };
		interrupt_handlers_[12] = []() { forward_interrupt(Pin::bcm_12); };
		interrupt_handlers_[13] = []() { forward_interrupt(Pin::bcm_13); };
		interrupt_handlers_[14] = []() { forward_interrupt(Pin::bcm_14); };
		interrupt_handlers_[15] = []() { forward_interrupt(Pin::bcm_15); };
		interrupt_handlers_[16] = []() { forward_interrupt(Pin::bcm_16); };
		interrupt_handlers_[17] = []() { forward_interrupt(Pin::bcm_17); };
		interrupt_handlers_[18] = []() { forward_interrupt(Pin::bcm_18); };
		interrupt_handlers_[19] = []() { forward_interrupt(Pin::bcm_19); };
		interrupt_handlers_[20] = []() { forward_interrupt(Pin::bcm_20); };
		interrupt_handlers_[21] = []() { forward_interrupt(Pin::bcm_21); };
		interrupt_handlers_[22] = []() { forward_interrupt(Pin::bcm_22); };
		interrupt_handlers_[23] = []() { forward_interrupt(Pin::bcm_23); };
		interrupt_handlers_[24] = []() { forward_interrupt(Pin::bcm_24); };
		interrupt_handlers_[25] = []() { forward_interrupt(Pin::bcm_25); };
		interrupt_handlers_[26] = []() { forward_interrupt(Pin::bcm_26); };
		interrupt_handlers_[27] = []() { forward_interrupt(Pin::bcm_27); };
	}

	void Pi_io_manager::setup_wiring_pi()
	{
		auto result = 0;
		switch (scheme_)
		{
		case Number_scheme::wiring_pi:
			result = wiringPiSetup();
			break;
		case Number_scheme::physical:
			result = wiringPiSetupPhys();
			break;
		default:
			result = wiringPiSetupGpio();
		}

		if (result < 0) {
			std::ostringstream err_message;
			err_message << "Error setting up wiring pi, failed with error code " << result;
			throw std::runtime_error(err_message.str());
		}
	}

	void Pi_io_manager::release(Pin pin)
	{
		ios_[to_underlying(pin)] = false;
	}

	void Pi_io_manager::assert_is_free(Pin pin)
	{
		const auto pin_number = to_underlying(pin);
		if (pin_number < 0 || pin_number >= io_count)
		{
			std::ostringstream err_message;
			err_message << "Pin number " << pin_number << " is invalid!";
			throw std::logic_error(err_message.str());
		}
		if (ios_[pin_number])
		{
			std::ostringstream err_message;
			err_message << "Pin " << pin_number << " is already in use!";
			throw std::logic_error(err_message.str());
		}
	}

	void Pi_io_manager::handle_interrupt(Pin pin)
	{
		const auto pin_number = to_underlying(pin);

		if (!ios_[pin_number] || !event_handlers_[pin_number])
			return;

		event_handlers_[pin_number](pin);
	}


	void Pi_io_manager::forward_interrupt(Pin pin)
	{ // TODO michivo: processing the interrupt should be done in a different thread, but threading is out of scope for now
		instance().handle_interrupt(pin);
	}

	State Pi_io_manager::digital_read(const Pin_handle& pin) const
	{
		return State(digitalRead(map_pin(pin.get_pin())));
	}

	void Pi_io_manager::digital_write(const Pin_handle& pin, State state) const
	{
		digitalWrite(map_pin(pin.get_pin()), to_underlying(state));
	}

	void Pi_io_manager::set_callback(Pin pin, Edge_type edge_type, void(*callback)(void))
	{
		const auto result = wiringPiISR(map_pin(pin), map_edge_type(edge_type), callback);
		if (result < 0)
		{
			std::ostringstream error_message;
			error_message << "Error setting up interrupt handler for pin ";
			error_message << to_underlying(pin);
			throw std::runtime_error(error_message.str());
		}
	}

	void Pi_io_manager::set_pin_mode(Pin pin, Mode mode)
	{
		pinMode(map_pin(pin), map_mode(mode));
	}

	void Pi_io_manager::set_pull_up_down(Pin pin, Pull_up_down pud)
	{
		pullUpDnControl(map_pin(pin), map_pud(pud));
	}

	constexpr int Pi_io_manager::map_pin(Pin pin)
	{
		return scheme_ == Number_scheme::wiring_pi ? wiring_pi_number(pin) :
			scheme_ == Number_scheme::physical ? physical_number(pin) :
			bcm_number(pin);
	}

	constexpr int Pi_io_manager::map_edge_type(Edge_type edge)
	{
		return edge == Edge_type::rising ? INT_EDGE_RISING :
			edge == Edge_type::falling ? INT_EDGE_FALLING :
			edge == Edge_type::both ? INT_EDGE_BOTH :
			INT_EDGE_SETUP;
	}

	constexpr int Pi_io_manager::map_mode(Mode mode)
	{
		return mode == Mode::in ? INPUT :
			mode == Mode::out ? OUTPUT :
			PWM_OUTPUT;
	}

	constexpr int Pi_io_manager::map_pud(Pull_up_down pud)
	{
		return pud == Pull_up_down::off ? PUD_OFF :
			pud == Pull_up_down::down ? PUD_DOWN :
			PUD_UP;
	}

	Pin_handle Pi_io_manager::register_output(Pin pin)
	{
		assert_is_free(pin);

		const auto pin_number = to_underlying(pin);

		Pin_handle result{ pin };
		set_pin_mode(pin, Mode::out);
		ios_[pin_number] = true;
		return result;
	}

	Pin_handle Pi_io_manager::register_input(Pin pin, std::function<void(Pin)> event_handler,
		Pull_up_down pud, Edge_type edge_type)
	{
		assert_is_free(pin);

		const auto pin_number = to_underlying(pin);
		set_pin_mode(pin, Mode::in);
		set_pull_up_down(pin, pud);
		if(event_handler)
			set_callback(pin, edge_type, interrupt_handlers_[pin_number]);

		Pin_handle result{ pin };
		ios_[pin_number] = true;
		event_handlers_[pin_number] = event_handler;
		return result;
	}

}
