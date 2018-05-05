#include <wiringPi.h>
#include <iostream>
#include <sstream>
#include <chrono>		//for timing conditions

#include "DigitalInputPi.h"
#include "PinPi.h"
#include "DigitalOutputPi.h"
#include "ReactionGame.h"
#include "TestFunctions.h"
#include "../ReactionGame/Files_Patrick_old/GameSetup.h"


void isr_button_player_1();
void isr_button_player_2();
void spy_btn_status(pi_io::Digital_input_pi btn1, pi_io::Digital_input_pi btn2);

// Global variables for button Player1 and Player2
bool btn_hit_p1;
bool status_btn_p1;
int64_t time_last_hit_p1;

bool btn_hit_p2;
bool status_btn_p2;
int64_t time_last_hit_p2;

int main()
{
	// Setup Wiring PI - Note: further calls do not change the Setup
	wiringPiSetup();

	// IO Config
	//
	using namespace pi_io;

	// setup Input Button	
	//
	const Digital_input_pi btn_player_1{ pi_io::e_pin::bcm_0, e_pull_up_down::up, pi_io::e_edge_type::falling, &isr_button_player_1 };
	const Digital_input_pi btn_player_2{ pi_io::e_pin::bcm_1, pi_io::e_pull_up_down::up, pi_io::e_edge_type::falling, &isr_button_player_2 };

	// setup Output LED's
	//
	const Digital_output_pi led_player_1{ pi_io::e_pin::bcm_2, pi_io::e_mode::out };
	const Digital_output_pi led_player_2{ pi_io::e_pin::bcm_3, pi_io::e_mode::out };
	const Digital_output_pi led_status{ pi_io::e_pin::bcm_4, pi_io::e_mode::out };

	// Game setup - read usernames and number of plays from the CLI
	//
	Game_setup reaction_setup;
	std::string player_name_1;
	std::string player_name_2;

	reaction_setup.print_setup_mask();

	pi_game::Player p1{ reaction_setup.read_usernames_CLI() };	//create player 1 
	pi_game::Player p2{ reaction_setup.read_usernames_CLI() };	//create player 2

	// setup Reaction Game
	pi_game::Reaction_game the_game{ reaction_setup.read_num_plays_CLI() };	//start game by setting number of rounds

	// turn all LEDs off
	led_player_1.set_digital_output_false();
	led_player_2.set_digital_output_false();
	led_status.set_digital_output_false();

	// print countdown, if players are ready
	reaction_setup.print_gamecountdown();

	the_game.set_allready_played_rounds(0);
	the_game.set_round_time();
	the_game.calc_status_time();
	the_game.set_over_all_active(TRUE);
	the_game.set_active_round(TRUE);

	// get actual time
	auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	auto act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	
	constexpr long three_second = 3000000;		// for microsecond calc time

	while (the_game.get_over_all_active())
	{
		//get actual time - each duration
		sys_now = std::chrono::system_clock::now().time_since_epoch();
		act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();

		if (the_game.get_active_round())
		{
			// set status led
			if ((the_game.get_statusled_time() - act_time) < 0)
			{
				led_status.set_digital_output_true();
			}

			// terminate the game after 3 secound inactivity --> next round
			if((act_time - the_game.get_statusled_time()) > three_second)
			{
				the_game.set_active_round(FALSE);
				the_game.set_allready_played_rounds_plus_one();
				the_game.set_time_next_round(act_time + three_second);
				//the_game.set_allready_played_rounds(the_game.get_rounds());
				std::cout << "Game derminated! - Nobody reacted :'( " << std::endl;
			}

			//determine the winner !
			if (btn_hit_p1 || btn_hit_p2)
			{
				//set game status to FALSE and calc the winner led runtime
				the_game.set_active_round(FALSE);
				the_game.set_time_next_round(act_time + three_second);
				the_game.set_allready_played_rounds_plus_one();

				if (the_game.get_statusled_time() < time_last_hit_p1)
				{
					if (btn_hit_p2 == false)
					{
						the_game.set_player_led(led_player_1);						
						p1.set_won_rounds_plus_one();
						//the_game.show_winner(p1,led_player_1);
					}
					else if (the_game.get_statusled_time() < time_last_hit_p2)
					{
						if (time_last_hit_p1 < time_last_hit_p2)
						{
							the_game.set_player_led(led_player_1);
							p1.set_won_rounds_plus_one();
							//the_game.show_winner(p1, led_player_1);
						}
						else
						{
							the_game.set_player_led(led_player_2);
							p2.set_won_rounds_plus_one();
							//the_game.show_winner(p2, led_player_2);
						}
					}
				}
				else if (the_game.get_statusled_time() < time_last_hit_p2)
				{
					the_game.set_player_led(led_player_2);
					p2.set_won_rounds_plus_one();
					//the_game.show_winner(p2, led_player_2);
				}

				// get the false start winner
				else
				{
					if (btn_hit_p2 && btn_hit_p1)
					{
						if (time_last_hit_p1 < time_last_hit_p2)
						{
							the_game.set_player_led(led_player_2);
							p2.set_won_rounds_plus_one();
							//the_game.show_winner(p2, led_player_2);
						}
						else
						{
							the_game.set_player_led(led_player_1);
							p1.set_won_rounds_plus_one();
							//the_game.show_winner(p1, led_player_1);
						}
					}
					else if (btn_hit_p1)
					{
						the_game.set_player_led(led_player_2);
						p2.set_won_rounds_plus_one();
						//the_game.show_winner(p2, led_player_2);
					}
					else
					{
						the_game.set_player_led(led_player_1);
						p1.set_won_rounds_plus_one();
						//the_game.show_winner(p1, led_player_1);
					}
				}
			}
		}

		// show winner led for 3 seconds
		// start next round
		if ((the_game.get_active_round() == false) && ((the_game.get_time_next_round() - act_time) < 0))
		{
			//reset btn_hit's
			btn_hit_p1 = FALSE;
			btn_hit_p2 = FALSE;

			std::cout << "Next round started!" << std::endl;
			the_game.set_active_round(TRUE);
			the_game.set_round_time();
			the_game.calc_status_time();

			// turn all LEDs off
			led_player_1.set_digital_output_false();
			led_player_2.set_digital_output_false();
			led_status.set_digital_output_false();
		}

		if(the_game.get_rounds() == the_game.get_allready_played_rounds())
		{
			// turn all LEDs off
			led_player_1.set_digital_output_false();
			led_player_2.set_digital_output_false();
			led_status.set_digital_output_false();

			the_game.set_over_all_active(FALSE);
			std::cout << std::endl << "All rounds played!" << std::endl;
		}

		spy_btn_status(btn_player_1, btn_player_2);		//Would be better in a timer isr all 10ms but didn't found anything in "www" how to do! ;-(
		delay(20);
	}

	//determine final score
	//
	std::cout << p1.get_username() << " has won " << p1.get_won_rounds() << " rounds."<< std::endl;
	std::cout << p2.get_username() << " has won " << p2.get_won_rounds() << " rounds." << std::endl;

	test::play_with_leds(led_player_1, led_player_2, led_status);

	return 0;
}


constexpr long debounce_time = 200000;

void isr_button_player_1()
{
	//get actual system time and convert it into us
	auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	auto int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	static int64_t last_int_time_btn;

	if (((int_time_btn - last_int_time_btn) > debounce_time) && (status_btn_p1))	//debounce button
	{
		//std::cout << std::endl << "Button 1 was pressed." << std::endl;
		if (btn_hit_p1 == false)
		{
			btn_hit_p1 = TRUE;
			time_last_hit_p1 = int_time_btn;
		}

		last_int_time_btn = int_time_btn;
	}
}


void isr_button_player_2()
{
	//get actual system time and convert it into us
	auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	auto int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	static int64_t last_int_time_btn;

	if (((int_time_btn - last_int_time_btn) > debounce_time) && (status_btn_p2))
	{
		//std::cout << std::endl << "Button 2 was pressed." << std::endl;
		if (btn_hit_p2 == false)
		{
			btn_hit_p2 = TRUE;
			time_last_hit_p2 = int_time_btn;
		}

		last_int_time_btn = int_time_btn;
	}
}

void spy_btn_status(pi_io::Digital_input_pi btn_player_1, pi_io::Digital_input_pi btn_player_2)
{
	static bool status_last_btn_p1 = HIGH;
	static bool status_last_btn_p2 = HIGH;

	const auto act_status_btn1 = btn_player_1.get_digital_input();
	const auto act_status_btn2 = btn_player_2.get_digital_input();

	if(act_status_btn1 == status_last_btn_p1)
	{
		status_btn_p1 = status_last_btn_p1;
	}

	if (act_status_btn2 == status_last_btn_p2)
	{
		status_btn_p2 = status_last_btn_p2;
	}

	status_last_btn_p1 = act_status_btn1;
	status_last_btn_p2 = act_status_btn2;
}


