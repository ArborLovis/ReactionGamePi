#include "ReactionGame.h"
#include <iostream>

namespace pi_game
{
	Reaction_game::Reaction_game(unsigned int const number_of_rounds) : rounds_to_play_{number_of_rounds}
	{
		time_round_starts_ = 0;
		time_status_led_ = 0;
	}

	unsigned int Reaction_game::get_rounds() const
	{
		return rounds_to_play_;
	}

	void Reaction_game::set_round_time()
	{
		const auto sys_now = std::chrono::system_clock::now().time_since_epoch();
		this->time_round_starts_ = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	}

	constexpr long five_seconds = 5000000;
	constexpr short five_milli_seconds = 5000;
	constexpr short one_thousand = 1000;

	void Reaction_game::calc_status_time()
	{
		// init random seed
		srand(time(nullptr));

		//get randome time between 1 and 5 seconds
		//
		int64_t time_secret = rand() % five_milli_seconds;
		time_secret = time_secret * one_thousand;

		//std::cout << "Das ist die geheime Nummer: " << time_secret << std::endl;
		
		//add to random time 5 seconds to get the range 5 - 10 seconds
		//
		time_status_led_ = (time_round_starts_ + five_seconds + time_secret);

		//std::cout << "Das ist die Rundenzahl: " << time_round_starts_ << std::endl;
		//std::cout << "Das ist die Startzahl : " << time_status_led_ << std::endl;
	}

	int64_t Reaction_game::get_statusled_time() const
	{
		return time_status_led_;
	}

	int64_t Reaction_game::get_round_time() const
	{
		return time_round_starts_;
	}

	void Reaction_game::set_player_led(pi_io::Digital_output_pi led)
	{
		led.set(true);
	}

	void Reaction_game::set_active_round(bool status)
	{
		round_active_ = status;
	}

	bool Reaction_game::get_active_round()
	{
		return round_active_;
	}

	void Reaction_game::set_allready_played_rounds(int count)
	{
		rounds_allready_played_ = count;
	}

	void Reaction_game::set_allready_played_rounds_plus_one()
	{
		rounds_allready_played_++;
	}

	unsigned int Reaction_game::get_allready_played_rounds()
	{
		return rounds_allready_played_;
	}

	void Reaction_game::set_time_next_round(int64_t time)
	{
		time_next_round_ = time;
	}

	int64_t Reaction_game::get_time_next_round()
	{
		return time_next_round_;
	}

	void Reaction_game::set_over_all_active(bool status)
	{
		over_all_active_ = status;
	}

	bool Reaction_game::get_over_all_active()
	{
		return over_all_active_;
	}

	void Reaction_game::show_winner(Player p, pi_io::Digital_output_pi led)
	{
		p.set_won_rounds_plus_one();
		led.set(true);
	}
}
