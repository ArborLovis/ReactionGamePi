#include "GameSetup.h"
#include "../piproxy.h"

#include <sstream>
#include <limits>
#include <iostream>
#include "../Player.h"

std::string Game_setup::default_name_ = "undefined";
std::vector<std::string> Game_setup::user_database_;

Game_setup::Game_setup() : username_{ default_name_ }
{}

void Game_setup::print_setup_mask() const
{
	std::cout << std::endl << "The Reaction Game" << std::endl;

	std::cout << std::endl << "NOTE: This is a reaction game between two players.";
	std::cout << "Each player has to press the butten as fast as he/she can after a indicator lamp turns on";
	std::cout << "In each round, the game is enabled after 5 to 10 seconds randomly";
	std::cout << "If the indicator lamp turns on, each player has the chance to hit the button first within 3 seconds";
	std::cout << "The fastest player gets an point and the next round starts" << std::endl;
	std::cout << "For pressing the button too early, the player which pressed wrong frist looses this round!" << std::endl << std::endl;

	std::cout << "LETs START WITH THE GAME!" << std::endl;
}

std::string Game_setup::read_usernames_CLI()
{
	std::string user = default_name_;

	std::cout << std::endl << "Please enter your username: ";
	getline(std::cin, user);
	std::stringstream in_username{ user };

	if (in_username >> user)
	{
		return user;
	}
	else
	{
		std::cout << "Sorry, something went wrong" << std::endl;
		user = default_name_;
		return user;
	}
}

unsigned int Game_setup::read_num_plays_CLI() const
{
	int number_plays = 0;

	std::cout << std::endl << "How many rounds do you want do play?" << std::endl;
	std::cout << "NOTE: Value should be grater than 0!" << std::endl << std::endl;

	while(number_plays == 0)
	{
		std::cout << "Enter max. round to be played: ";
		std::string s_num_plays;
		std::cin >> s_num_plays;
		
		std::string::size_type sz;		// --> why??? || Sorce: http://www.cplusplus.com/reference/string/stoi/ (21.04.2018)		
		number_plays = stoi(s_num_plays, &sz, 10);	//convert input string to an integer (base 10, is also default -> not necessary)
		if (number_plays <= 0)
		{
			number_plays = 0;
			std::cout << std::endl << "DAMN, you did not listen!!! Try again!" << std::endl << std::endl;
		}
	}
	
	std::cout << std::endl << "YEAH, you are going to play " << number_plays << " rounds!" << std::endl;
	std::cout << std::endl << "Now, get the game started!" << std::endl;

	return number_plays;
}

void Game_setup::print_gamecountdown()
{
	constexpr short one_second = 1000;				// for millisecond delay

	// clear input buffer
	fflush(stdin);

	int c;
	while ((c = getchar()) != EOF && c != '\n'); 	

	// start game
	std::cout << std::endl << "If you are ready, press Enter to start the game in 3 seconds!";
	std::cout << std::endl;
	getchar();
	std::cout << "... 3" << std::endl;
	delay(one_second);
	std::cout << "... 2" << std::endl;
	delay(one_second);
	std::cout << "... 1" << std::endl;
	delay(one_second);

	std::cout << std::endl << "Game started!" << std::endl << std::endl;
}

unsigned short Game_setup::get_number_players() const
{
	return user_database_.size();
}

void Game_setup::add_user(std::string name)
{
	user_database_.push_back(name);
}

void Game_setup::delete_user(std::string const name)
{
	auto enable_swap = 0;
	auto space = -1;

	for(auto& it : user_database_)
	{
		auto cnt = 0;

		if (name == it)
		{
			it = default_name_;
			enable_swap = 1;
			space = cnt;
			std::cout << name << " has been destroyed!" << std::endl;
		}

		if(enable_swap)	//reorder users
		{
			if(it != user_database_.back())
			{
				std::cout << it << " and " << user_database_.back() << std::endl;
				user_database_.at(space) = user_database_.at(space + 1);
				space++;
				user_database_.at(space) = default_name_;
			}
		}
		cnt++;
	}
	if(!user_database_.empty())
		user_database_.pop_back();	//delete last element
}

bool Game_setup::check_user_exists(std::string name) const
{
	if(!user_database_.empty())
	{
		for (auto& it : user_database_)
		{
			if(it == name)
			{
				//std::cout << "User allready exists!" << std::endl;
				return false;
			}
		}
	}
	return true;
}

void Game_setup::print_database_cli() const
{
	//std::cout << std::endl << "+++ Statistic begins +++" << std::endl;
	for(auto& it: user_database_)
	{
		std::cout << it << std::endl;
	}
}

/*
 	std::string user = default_name;
	static unsigned short cnt_player = 0;
			
		while(cnt_player != 2)
		{ // MFA - this implementation is somehow awkward. why don't you have one method that reads a user name and call it twice, once for each player?
			std::cout << std::endl << "Player " << ++cnt_player << ", please enter YOUR username: ";
			getline(std::cin, user);
			std::stringstream in_username{ user };
			if (in_username >> user)
			{
				if(first_user_ == default_name)
				{
					first_user_ = user;
					std::cout << "Great, your selected username is: " << user << std::endl;
					return first_user_;
				}
				
				if((second_user_ == default_name) && (first_user_ != user))
				{
					second_user_ = user;
					std::cout << "Great, your selected username is: " << user << std::endl;
					return second_user_;
				}
				
				std::cout << std::endl << "Sorry, this username allready exists. Please try another!" << std::endl;
				user = default_name;
				cnt_player--;
			}
			else
			{
				user = default_name;
			}

		}
		return user; //useful??
 */



