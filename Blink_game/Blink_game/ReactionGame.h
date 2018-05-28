#pragma once
#include "Player.h"
#include "PiDigitalOutput.h"
#include "PinConfig.h"
#include "PiDigitalInput.h"

#include <mutex>
#include <condition_variable>

namespace reaction_game {

	class Reaction_game
	{
	public:
		Reaction_game(Player p1, Player p2, const Pin_config& cfg, int num_rounds);

		void play();

		void reset_for_round();

	private:
		Player p1_;
		Player p2_;
		int num_rounds_;
		pi_io::Pi_digital_output led_output_;
		pi_io::Pi_digital_input p1_button_;
		pi_io::Pi_digital_output p1_led_;
		pi_io::Pi_digital_input p2_button_;
		pi_io::Pi_digital_output p2_led_;
		std::condition_variable cv_;
		std::mutex mutex_;

		bool play_round();
		static void on_victory(Player& p, pi_io::Pi_digital_output& led);
		void handle_early_start();
		void check_result(const std::chrono::system_clock::time_point & on_time);
		static void on_overall_victory(pi_io::Pi_digital_output& led);
		void on_overall_tie();
		void on_button_pressed(Player& player);
	};

	Player create_player(int player_number);
}
