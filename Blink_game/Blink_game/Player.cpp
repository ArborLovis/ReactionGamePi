#include "Player.h"
#include <utility>
#include <iostream>

namespace reaction_game {

	Player::Player(std::string name) :
		name_{ std::move(name) }, win_count_{ 0 }
	{
	}

	std::string Player::name() const
	{
		return name_;
	}

	void Player::add_victory()
	{
		win_count_++;
	}

	int Player::victory_count() const
	{
		return win_count_;
	}

	void Player::on_button_pressed()
	{
		button_time_ = std::chrono::system_clock::now();
	}

	void Player::reset_button_time()
	{
		button_time_ = Time_point{};
	}

	bool Player::was_button_pressed() const
	{
		return button_time_ != Time_point{};
	}

	Player::Time_point Player::button_time() const
	{
		return button_time_;
	}

	Player create_player(int player_number)
	{
		std::string player_name;
		std::cout << "Player " << player_number << ", enter your name: ";
		std::cin >> player_name;
		return Player{ player_name };
	}
}
