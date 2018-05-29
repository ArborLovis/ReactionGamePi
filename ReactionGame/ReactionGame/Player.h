#pragma once
#include <string>

namespace pi_game
{
	
	class Player
	{
		public:
		Player(std::string name);
		Player(const Player &old_obj);		//cpy-constr
		Player& operator=(const Player& other);
		Player(Player&& other) noexcept;
		Player& operator=(Player&& rhs) noexcept;

		static Player create_player();
		std::string get_username() const;

		void set_won_rounds_plus_one();
		unsigned int get_won_rounds() const;
		~Player();

	private:
		std::string name_;
		unsigned int won_rounds_;

		static std::string default_name_;
	};
}