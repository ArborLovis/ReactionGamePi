#pragma once

#include "Pin.h"

namespace pi_io {

	class Pin_handle
	{
	public:
		Pin_handle(Pin pin);
		~Pin_handle();
		Pin_handle(Pin_handle &&other) noexcept;
		Pin_handle& operator=(Pin_handle &&other) noexcept;

		void release();
		Pin get_pin() const;

	private:
		Pin pin_;
		bool is_active_;
	};

}