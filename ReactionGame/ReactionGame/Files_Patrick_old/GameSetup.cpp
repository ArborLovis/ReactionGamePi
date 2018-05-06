#include "GameSetup.h"
#include <sstream>
#include <limits>
#include "pi_gpio_headers.h"

Game_setup::Game_setup() : first_user_{"undefined"}, second_user_{"undefined"}
{}

void Game_setup::print_setup_mask() const // MFA may be const
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

std::string Game_setup::read_usernames_CLI() // MFA naming: rename to something like 'add_users', then provide accessor methods for user names
{
	// MFA avoid magic constants like 'undefined' - what if you make a typo once?
	std::string user = "undefined"; // MFA curly braces not needed
	unsigned short cnt_player = 0;
			
		while(cnt_player != 2)
		{
			std::cout << std::endl << "Player " << ++cnt_player << ", please enter YOUR username: ";
			getline(std::cin, user);
			std::stringstream in_username{ user };
			if (in_username >> user) // MFA reading a string should be safe, i don't think all that error handling is needed
			{
				if(first_user_ == "undefined")
				{
					first_user_ = user;
					std::cout << "Great, your selected username is: " << user << std::endl;
					return first_user_;
					// MFA you could return first_user_ here right away!
					//first_user_.replace(first_user_.begin(), first_user_.end(), user);
				}
				else if((second_user_ == "undefined") && (first_user_ != user))
				{
					second_user_ = user;
					std::cout << "Great, your selected username is: " << user << std::endl;
					return second_user_;
					// MFA you could return second_user_ here right away!
				}
				else
				{
					std::cout << std::endl << "Sorry, this username allready exists. Please try another!" << std::endl;
					user = "undefined";
					cnt_player--;
				}
			}
			else
			{
				user = "undefined";
				//user.replace(user.begin(), user.end(), "undefined"); // MFA probably safe, but not clear. use 'user = "undefined"' instead
			}

		}
		return user; //useful??
}

std::string Game_setup::get_username(short const first_sec) const
{
	if (first_sec == 1)
		return first_user_;
	else if (first_sec)
		return second_user_;
	else
		return "undefind";
}

unsigned int Game_setup::read_num_plays_CLI() const
{
	std::string s_num_plays; // MFA move declaration closer to initialization
	int number_plays = 0; // MFA no hungarian notation, see cpp core guideline NL.5

	std::cout << std::endl << "How many rounds do you want do play?" << std::endl;
	std::cout << "NOTE: Value should be grater than 0!" << std::endl << std::endl;

	while(number_plays == false)	// MFA use boolean instead of 'not int'. this is C-style
	{
		std::cout << "Enter max. round to be played: ";
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
	std::cout << std::endl << "Now, get the game started!";

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





