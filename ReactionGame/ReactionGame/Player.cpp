#include "Player.h"
#include "./Files_Patrick_old/GameSetup.h"
#include <string>
#include <iostream>
#include <utility>

namespace pi_game
{	
	std::string Player::default_name_ = "undefined";

	Player::Player(std::string name) : name_{std::move(name)}, won_rounds_{ 0 }
	{
	}

	Player::Player(const Player & old_obj)
	{
		name_ = old_obj.name_;
		won_rounds_ = old_obj.won_rounds_;
		std::cout << std::endl << "Player: cpy - constr. called" << std::endl;
	}

	Player & Player::operator=(const Player & other)
	{
		std::cout << std::endl << "Player: cpy - operator called" << std::endl;

		//check for self assignment
		if (&other == this)
			return *this;
		else
		{
			name_ = other.name_;
			won_rounds_ = other.won_rounds_;
			return *this;
		}
	}

	Player::Player(Player && other) noexcept : name_{default_name_}, won_rounds_{0}
	{
		std::cout << std::endl << "Player: move - constr. called" << std::endl;

		name_ = other.name_;
		won_rounds_ = other.won_rounds_;

		other.name_ = default_name_;
		other.won_rounds_ = 0;
	}

	Player & Player::operator=(Player && rhs) noexcept
	{
		std::cout << std::endl << "Player: move assignment operator called" << std::endl;

		if(this != &rhs)
		{
			name_ = rhs.name_;
			won_rounds_ = rhs.won_rounds_;

			rhs.name_ = default_name_;
			rhs.won_rounds_ = 0;
		}
		return *this;
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
