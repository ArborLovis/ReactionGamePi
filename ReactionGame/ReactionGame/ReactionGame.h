#pragma once
#include "Player.h"
#include <chrono>
#include "DigitalOutputPi.h"

namespace pi_game
{
	class Reaction_game
	{
	public:
		Reaction_game(unsigned int const number_of_rounds);
		unsigned int get_rounds() const;
		void set_round_time();
		void calc_status_time();
		int64_t get_statusled_time() const;
		int64_t get_round_time() const;

		void set_player_led(pi_io::Digital_output_pi led);
		void set_active_round(bool status);
		bool get_active_round();

		void set_allready_played_rounds(int count);
		void set_allready_played_rounds_plus_one();
		unsigned int get_allready_played_rounds();

		void set_time_next_round(int64_t time);
		int64_t get_time_next_round();

		void set_over_all_active(bool status);
		bool get_over_all_active();

		void show_winner(Player p, pi_io::Digital_output_pi led);

	private:
		unsigned int rounds_to_play_;
		int64_t time_round_starts_;
		int64_t time_status_led_;
		int64_t time_next_round_;
		bool round_active_;
		int rounds_allready_played_;
		bool over_all_active_;
	};

}
