#pragma once
#include <string>

namespace pi_game
{
	
	class Player
	{
		public:
		Player(std::string name);
		std::string get_username() const;

		void set_won_rounds_plus_one();
		unsigned int get_won_rounds() const;

	private:
		std::string name_;
		unsigned int won_rounds_;


	};
}