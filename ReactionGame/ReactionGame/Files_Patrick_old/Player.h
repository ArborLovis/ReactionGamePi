#pragma once

#include "pi_gpio_headers.h"
#include <wiringPi.h>
#include <string>

class Player
{
public:
	Player(); // MFA do we need this?
	Player(std::string name);
	void set_username(std::string const name);
	std::string get_username() const;
	void set_result_round(game_outcome const result);
	void get_overall_reult(int* wins, int* losses); // MFA no pointers please. references are one solution, a distinct struct Game_result would be really nice!
	void set_start_time(unsigned long const start_time); // MFA you could use time_points instead of unsigned longs
	unsigned long get_reaction_time(unsigned long stop_time);

private:
	std::string username_;
	int wins_;
	int losses_;
	unsigned long start_time_;
	unsigned long react_time_; // MFA never used

};
