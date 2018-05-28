#include "ReactionGame.h"
#include "Enums.h"

#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>
#include <utility>

namespace reaction_game {
	using namespace std::chrono;
	using namespace std::literals::chrono_literals;

	Reaction_game::Reaction_game(Player p1, Player p2, const Pin_config& cfg, int num_rounds) :
		p1_{std::move(p1)},
		p2_{std::move(p2)},
		num_rounds_{ num_rounds },
		led_output_{ cfg.reaction_led() },
		p1_button_{ cfg.p1_button(), cfg.p1_pud(), pi_io::Edge_type::rising, [&](pi_io::Pin) { this->on_button_pressed(this->p1_); } },
		p1_led_{ cfg.p1_led() },
		p2_button_{ cfg.p2_button(), cfg.p2_pud(), pi_io::Edge_type::rising, [&](pi_io::Pin) { this->on_button_pressed(this->p2_); } },
		p2_led_{ cfg.p2_led() }
	{
	}

	void Reaction_game::play()
	{
		std::cout << "Starting game, get ready!" << std::endl;
		for (int i = 0; i < num_rounds_; i++)
		{
			if (!play_round())
			{
				std::cout << "Game aborted due to inactivity" << std::endl;
				return;
			}
			if (p1_.victory_count() > num_rounds_ / 2 || p2_.victory_count() > num_rounds_ / 2)
			{
				break;
			}
		}
		if (p1_.victory_count() > p2_.victory_count()) {
			on_overall_victory(p1_led_);
			std::cout << p1_.name() << " is the overall winner!" << std::endl;
			return;
		}

		if (p2_.victory_count() > p1_.victory_count()) {
			on_overall_victory(p2_led_);
			std::cout << p2_.name() << " is the overall winner!" << std::endl;
			return;
		}

		on_overall_tie();
		std::cout << "The result is an overall tie, you are both champs!" << std::endl;
	}

	void Reaction_game::reset_for_round()
	{
		led_output_ = pi_io::State::low;
		p1_led_ = pi_io::State::low;
		p2_led_ = pi_io::State::low;

		p1_.reset_button_time();
		p2_.reset_button_time();
	}

	bool Reaction_game::play_round()
	{
		constexpr auto max_wait_time = 8s;
		constexpr auto min_wait_time = 3s;
		constexpr auto max_reaction_time = 3s;

		reset_for_round();

		const auto wait_time = rand() % duration_cast<milliseconds>(max_wait_time - min_wait_time).count() +
			duration_cast<milliseconds>(min_wait_time).count();

		std::this_thread::sleep_for(milliseconds{ wait_time });
		const auto on_time = system_clock::now();
		led_output_ = pi_io::State::high;

		std::unique_lock<std::mutex> lock(mutex_);
		cv_.wait_for(lock, max_reaction_time);

		led_output_ = pi_io::State::low;
		if (!p1_.was_button_pressed() && !p2_.was_button_pressed())
		{
			return false;
		}

		check_result(on_time);
		return true;
	}

	void Reaction_game::on_victory(Player& p, pi_io::Pi_digital_output& led)
	{
		using namespace std::literals::chrono_literals;
		constexpr auto led_on_time = 3s;

		std::cout << p.name() << " - you won!" << std::endl;
		p.add_victory();
		led.set_state(pi_io::State::high);
		std::this_thread::sleep_for(led_on_time);
		led.set_state(pi_io::State::high);
	}

	void Reaction_game::handle_early_start()
	{
		if (p1_.was_button_pressed() && !p2_.was_button_pressed())
		{ // p1 was an early starter, p2 wins
			on_victory(p2_, p2_led_);
			return;
		}

		if (p2_.was_button_pressed() && !p1_.was_button_pressed())
		{ // p2 was an early starter, p1 wins
			on_victory(p1_, p1_led_);
			return;
		}

		if (p1_.button_time() < p2_.button_time())
		{ // p1 was the earlier starter, p2 wins
			on_victory(p2_, p2_led_);
		}
		else
		{ // p2 was the earlier starter, p1 wins
			on_victory(p1_, p1_led_);
		}
	}

	void Reaction_game::check_result(const std::chrono::system_clock::time_point& on_time)
	{
		if (p1_.was_button_pressed() && p1_.button_time() > on_time)
		{ // valid button press for p1_
			if (p2_.was_button_pressed() && p2_.button_time() > on_time)
			{ // valid button press for p2_
				if (p2_.button_time() < p1_.button_time())
				{
					on_victory(p2_, p2_led_);
					return;
				}
				if (p1_.button_time() < p2_.button_time())
				{
					on_victory(p1_, p1_led_);
					return;
				}

				std::cout << "This was a tie." << std::endl;
				return;
			}

			on_victory(p1_, p1_led_);
			return;
		}

		if (p2_.was_button_pressed() && p2_.button_time() > on_time)
		{ // valid button press for p2_
			on_victory(p2_, p2_led_);
			return;
		}

		handle_early_start();
	}

	void Reaction_game::on_overall_victory(pi_io::Pi_digital_output& led)
	{
		constexpr auto blink_time = 500ms;

		for (int i = 0; i < 5; i++)
		{
			led = pi_io::State::high;
			std::this_thread::sleep_for(blink_time);
			led = pi_io::State::low;
			std::this_thread::sleep_for(blink_time);
		}
	}

	void Reaction_game::on_overall_tie()
	{
		using namespace std::literals::chrono_literals;
		constexpr auto blink_time = 500ms;

		for (int i = 0; i < 5; i++)
		{
			p1_led_ = pi_io::State::high;
			p2_led_ = pi_io::State::high;
			std::this_thread::sleep_for(blink_time);
			p1_led_ = pi_io::State::low;
			p2_led_ = pi_io::State::low;
			std::this_thread::sleep_for(blink_time);
		}
	}

	void Reaction_game::on_button_pressed(Player& player)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		player.on_button_pressed();
		cv_.notify_one();
	}
}
