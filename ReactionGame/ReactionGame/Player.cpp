#include "Player.h"
#include <iostream>
#include "IoFunctionsPi.h"

namespace pi_game
{
	
	player::player(std::string name)
	{
		name_ = name;
		won_rounds_ = 0;
	}

	std::string player::get_username() const
	{
		return name_;
	}

	void player::set_won_rounds_plus_one()
	{
		won_rounds_++;
		//std::cout << "We are here. Playername = " << name_ << " Winnings = " << won_rounds_ << std::endl;
	}

	unsigned int player::get_won_rounds() const
	{
		return won_rounds_;
	}
}
