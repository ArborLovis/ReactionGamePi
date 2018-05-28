#include "Player.h"
#include "./Files_Patrick_old/GameSetup.h"
#include <string>
#include <iostream>

namespace pi_game
{	
	Player::Player(std::string name) : name_{ name }, won_rounds_{ 0 }
	{
		Game_setup user_handling;
		user_handling.add_user(name_);	//Note for me: error handling should be implemented
	}

	Player Player::create_player() 
	{
		Game_setup read_name;
		std::string name = read_name.read_usernames_CLI();
		
		while (!read_name.check_user_exists(name))
		{
			name = read_name.read_usernames_CLI();
		}
		read_name.add_user(name);

		Player p{ name };
		return p;
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

	Player::~Player()
	{
		Game_setup::delete_user(name_);
	}
}
