#pragma once

#include <string>
#include <chrono>

namespace reaction_game {

	class Player
	{
		typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> Time_point;

	public:
		Player(std::string name);

		std::string name() const;

		void add_victory();

		int victory_count() const;

		void on_button_pressed();

		void reset_button_time();

		bool was_button_pressed() const;

		Time_point button_time() const;

	private:
		std::string name_;
		int win_count_;
		Time_point button_time_;
	};

}