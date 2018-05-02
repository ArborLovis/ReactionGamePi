#include "ReactionGame.h"
#include <iostream>

namespace pi_game
{
	reaction_game::reaction_game()
	{
		time_round_starts_ = 0;
		time_status_led_ = 0;
		//std::cout << "Creat a new Reactiongame instance!" << std::endl;

		std::cout << "How many rounds do you want to play? ";
		unsigned int count = 0;

		const auto max_num_rounds = 100;
		const auto min_num_rounds = 1;

		if (!(std::cin >> count) || count < min_num_rounds || count > max_num_rounds)
		{
			std::cout << "Invalid number of rounds, enter a number between "
				<< min_num_rounds << " and " << max_num_rounds << std::endl;
		}
		rounds_to_play_ = count;

	}
	unsigned int reaction_game::get_rounds() const
	{
		return rounds_to_play_;
	}
	void reaction_game::set_round_time()
	{
		const auto sys_now = std::chrono::system_clock::now().time_since_epoch();
		this->time_round_starts_ = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	}

#define FIVE_SECONDS 5000000
#define FIVE_MILLI_SECONDS 5000
#define ONE_THOUSAND 1000

	void reaction_game::calc_status_time()
	{
		// init random seed
		srand(time(nullptr));

		int64_t time_secret = rand() % FIVE_MILLI_SECONDS;
		time_secret = time_secret * ONE_THOUSAND;

		//std::cout << "Das ist die geheime Nummer: " << time_secret << std::endl;
		

		time_status_led_ = (time_round_starts_ + FIVE_SECONDS + time_secret);

		//std::cout << "Das ist die Rundenzahl: " << time_round_starts_ << std::endl;
		//std::cout << "Das ist die Startzahl : " << time_status_led_ << std::endl;
	}
	int64_t reaction_game::get_statusled_time() const
	{
		return time_status_led_;
	}
	int64_t reaction_game::get_round_time() const
	{
		return time_round_starts_;
	}
	void reaction_game::set_player_led(pi_io::digital_output_pi led)
	{
		led.set_digital_output_true();
	}
	void reaction_game::set_active_round(bool status)
	{
		round_active_ = status;
	}
	bool reaction_game::get_active_round()
	{
		return round_active_;
	}
	void reaction_game::set_allready_played_rounds(int count)
	{
		rounds_allready_played_ = count;
	}
	void reaction_game::set_allready_played_rounds_plus_one()
	{
		rounds_allready_played_++;
	}
	unsigned int reaction_game::get_allready_played_rounds()
	{
		return rounds_allready_played_;
	}
	void reaction_game::set_time_next_round(int64_t time)
	{
		time_next_round_ = time;
	}
	int64_t reaction_game::get_time_next_round()
	{
		return time_next_round_;
	}
	void reaction_game::set_over_all_active(bool status)
	{
		over_all_active_ = status;
	}
	bool reaction_game::get_over_all_active()
	{
		return over_all_active_;
	}
	void reaction_game::show_winner(player p, pi_io::digital_output_pi led)
	{
		p.set_won_rounds_plus_one();
		led.set_digital_output_true();
	}
}
