#pragma once

#include "../piproxy.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "pi_gpio_headers.h"

namespace pi_game {
	class Player;
}

class Game_setup
{
public:
	Game_setup();
	void print_setup_mask() const; // MFA may be const
	std::string read_usernames_CLI(); // MFA you should prefer one method that reads both player names
	unsigned int read_num_plays_CLI() const;
	static void print_gamecountdown();

	unsigned short get_number_players() const;
	void add_user(std::string name);
	static void delete_user(std::string const name);
	bool check_user_exists(std::string name) const;
	void print_database_cli() const;

private:
	std::string username_;
	//std::string second_user_;
	static std::string default_name_;
	static std::vector<std::string> user_database_;
};
