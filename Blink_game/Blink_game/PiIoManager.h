#pragma once
#include "Pin.h"
#include "Enums.h"
#include "PinHandle.h"

#include <array>
#include <functional>

namespace pi_io {

	class Pi_io_manager
	{
	public:
		static Pi_io_manager& instance()
		{
			static Pi_io_manager instance_;
			return instance_;
		}

		Pi_io_manager(const Pi_io_manager &other) = delete;
		Pi_io_manager(Pi_io_manager &&other) = default;

		Pi_io_manager& operator=(const Pi_io_manager& rhs) = delete;
		Pi_io_manager& operator=(Pi_io_manager&& rhs) = default;

		~Pi_io_manager() = default;

		Pin_handle register_output(Pin pin);
		Pin_handle register_input(Pin pin, std::function<void(Pin)> event_handler,
			Pull_up_down pud = Pull_up_down::up, Edge_type edge_type = Edge_type::rising);

		State digital_read(const Pin_handle& pin) const;
		void digital_write(const Pin_handle& pin, State state) const;

	private:
		void setup_interrupt_handlers();
		Pi_io_manager();

		static void setup_wiring_pi();
		void release(Pin pin);
		void assert_is_free(Pin pin);
		void handle_interrupt(Pin pin);

		static void set_callback(Pin pin, Edge_type edge_type, void(*callback)(void));
		static void set_pin_mode(Pin pin, Mode mode);
		static void set_pull_up_down(Pin pin, Pull_up_down pud);
		static void forward_interrupt(Pin pin);

		static constexpr int io_count = 28;

		std::array<void(*)(), io_count> interrupt_handlers_{}; // for 'incoming' interrupts. those are forwarded to event handlers
		std::array<std::function<void(Pin)>, io_count> event_handlers_;
		std::array<bool, io_count> ios_{};

		enum class Number_scheme { bcm, wiring_pi, physical };

		constexpr static Number_scheme scheme_ = Number_scheme::bcm;
		static constexpr int map_pin(Pin pin);
		static constexpr int map_edge_type(Edge_type edge);
		static constexpr int map_mode(Mode mode);
		static constexpr int map_pud(Pull_up_down pud);

		friend Pin_handle;
	};

}