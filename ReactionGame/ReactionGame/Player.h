#pragma once
#include <string>

namespace pi_game
{
	
	class Player
	{
		public:
		Player(std::string name);
		static Player create_player();
		std::string get_username() const;

		void set_won_rounds_plus_one();
		unsigned int get_won_rounds() const;
		~Player();

	private:
		std::string name_;
		unsigned int won_rounds_;


	};
}