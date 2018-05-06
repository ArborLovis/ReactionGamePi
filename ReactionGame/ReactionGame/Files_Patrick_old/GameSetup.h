#pragma once

#include <wiringPi.h>
#include <string>
#include <iostream>
#include <sstream>

#include "pi_gpio_headers.h"

class Game_setup
{
public:
	Game_setup();
	void print_setup_mask() const; // MFA may be const
	std::string read_usernames_CLI(); // MFA you should prefer one method that reads both player names
	std::string get_username(short const first_sec) const;
	unsigned int read_num_plays_CLI() const;
	static void print_gamecountdown();

private:
	std::string first_user_;
	std::string second_user_;
};