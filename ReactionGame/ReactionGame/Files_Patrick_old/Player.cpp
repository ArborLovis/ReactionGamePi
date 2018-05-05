#include "Player.h"
#include <iostream>

Player::Player() : username_{"undefined"}, wins_{0}, losses_{0}, start_time_{0}, react_time_{0}
{
}

Player::Player(std::string name) : username_{name}, wins_{ 0 }, losses_{ 0 }, start_time_{ 0 }, react_time_{ 0 }
{
}

void Player::set_username(std::string const name)
{
	username_ = name;
}

std::string Player::get_username() const
{
	return username_;
}

void Player::set_result_round(game_outcome const result)
{
	if ((result == game_outcome::WIN) || (result == game_outcome::TIE))
		wins_++;
	else if ((result == game_outcome::LOSS))
		losses_++;
	else
		std::cout << std::endl << "ERROR, false game result was entered!" << std::endl;
}

void Player::get_overall_reult(int * wins, int * losses) // MFA reult => result. and this could be const!
{
	*wins = wins_;
	*losses = losses_;
}

void Player::set_start_time(unsigned long const start_time)
{
	start_time_ = start_time;
}

unsigned long Player::get_reaction_time(unsigned long stop_time) // MFA could be const!
{
	if (start_time_ > stop_time)
		return (start_time_ - stop_time);
	else
		return 0;
}
