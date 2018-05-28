// nested class Pin_handle
#include "PinHandle.h"
#include "PiIoManager.h"

namespace pi_io {

	Pin_handle::Pin_handle(Pin pin) : pin_{ pin }, is_active_{ true }
	{
	}

	Pin_handle::~Pin_handle()
	{
		if (is_active_)
		{
			Pi_io_manager::instance().release(pin_);
		}
	}

	Pin_handle::Pin_handle(Pin_handle&& other) noexcept : pin_{ other.pin_ }, is_active_{ other.is_active_ }
	{
		other.is_active_ = false;
	}

	Pin_handle& Pin_handle::operator=(Pin_handle&& other) noexcept
	{
		is_active_ = other.is_active_;
		pin_ = other.pin_;
		other.is_active_ = false;

		return *this;
	}

	void Pin_handle::release()
	{
		Pi_io_manager::instance().release(pin_);
		is_active_ = false;
	}

	Pin Pin_handle::get_pin() const
	{
		return pin_;
	}

}