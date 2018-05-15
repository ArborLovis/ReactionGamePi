#include "Player.h"
#include <iostream>

namespace pi_game
{
	
	Player::Player(std::string name)
	{
		name_ = name;
		won_rounds_ = 0;
	}

	std::string Player::get_username() const
	{
		return name_;
	}

	void Player::set_won_rounds_plus_one()
	{
		won_rounds_++;
		//std::cout << "We are here. Playername = " << name_ << " Winnings = " << won_rounds_ << std::endl;
	}

	unsigned int Player::get_won_rounds() const
	{
		return won_rounds_;
	}
}
