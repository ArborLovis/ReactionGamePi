#include "piproxy.h"
#include <iostream>
#include <sstream>
#include <chrono>		//for timing conditions
#include <fstream>
#include <stdexcept>

#include "DigitalInputPi.h"
#include "DigitalOutputPi.h"
#include "ReactionGame.h"
#include "TestFunctions.h"
#include "../ReactionGame/Files_Patrick_old/GameSetup.h"
#include "Manage_Io.h"
#include "json.hpp"
#include "IoFunctionsPi.h"

#define SWITCH_EXCEPTION_TEST

void isr_button_player_1();
void isr_button_player_2();
void spy_btn_status(pi_io::Digital_input_pi btn_player_1, pi_io::Digital_input_pi btn_player_2);
nlohmann::json read_config(std::string file_name);

void test_exception()
{
	throw std::invalid_argument("Test Exception");
}

// Global variables for button Player1 and Player2
bool btn_hit_p1;
bool status_btn_p1;
int64_t time_last_hit_p1;

bool btn_hit_p2;
bool status_btn_p2;
int64_t time_last_hit_p2;

int main()
{
	try
	{
		// Setup Wiring PI - Note: further calls do not change the Setup
		wiringPiSetup();

		// IO Config
		//
		using namespace pi_io;

		// reading IO_pins from json file

		nlohmann::json j_object = read_config("pins.json");

		// setup Input Button	
		//
		const Digital_input_pi btn_player_1{ map_pin_numbers(j_object["p1_button"].get<int>()),
			Pull_up_down::up, Edge_type::falling, &isr_button_player_1 };
		const Digital_input_pi btn_player_2{ map_pin_numbers(j_object["p2_button"].get<int>()),
			Pull_up_down::up, Edge_type::falling, &isr_button_player_2 };

		// setup Output LED's
		//
		const Digital_output_pi led_player_1{ map_pin_numbers(j_object["p1_led"].get<int>()), Mode::out };
		const Digital_output_pi led_player_2{ map_pin_numbers(j_object["p2_led"].get<int>()), Mode::out };
		const Digital_output_pi led_status{ map_pin_numbers(j_object["state"].get<int>()), Mode::out };

		// Game setup - read usernames and number of plays from the CLI
		//
		Game_setup reaction_setup;

		pi_game::Player p1 = pi_game::Player::create_player();
		reaction_setup.print_database_cli();
		pi_game::Player p2 = pi_game::Player::create_player();
		reaction_setup.print_database_cli();

		// setup Reaction Game
		pi_game::Reaction_game the_game{ reaction_setup.read_num_plays_CLI() };	//start game by setting number of rounds

		// turn all LEDs off
		led_player_1.set(false);
		led_player_2.set(false);
		led_status.set(false);

		// print countdown, if players are ready	
		Game_setup::print_gamecountdown();

		// reset game statistic
		//
		the_game.set_allready_played_rounds(0);
		the_game.set_round_time();
		the_game.calc_status_time();
		the_game.set_over_all_active(TRUE);
		the_game.set_active_round(TRUE);

		// get actual time
		auto sys_now = std::chrono::system_clock::now().time_since_epoch();
		auto act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	
		constexpr long three_second = 3000000;		// for microsecond calc time

		//start the reaction game
		//
		while (the_game.get_over_all_active())
		{
			//get actual time - each duration
			sys_now = std::chrono::system_clock::now().time_since_epoch();
			act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();

			if (the_game.get_active_round())	
			{
				// --- TIMING RELEVANT --- // BEGIN
				// turn on status led
				if ((the_game.get_statusled_time() - act_time) < 0)	//turn on led between 5 - 10 seconds
				{
					led_status.set(true);
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
				// --- TIMING RELEVANT --- // END

				// --- Look at hardware --- // 
				//determine the winner !
				if (btn_hit_p1 || btn_hit_p2)
				{
					//set game status to FALSE (=round ends) and calc the winner led runtime
					the_game.set_active_round(FALSE);
					the_game.set_time_next_round(act_time + three_second);
					the_game.set_allready_played_rounds_plus_one();				//maybe "inc_num_rounds_played": -> shorter

					if (the_game.get_statusled_time() < time_last_hit_p1)	//btn pressed after 3 seconds?
					{
						if (!btn_hit_p2)	//player 2 did not react, player 1 wins
						{
							the_game.set_player_led(led_player_1);						
							p1.set_won_rounds_plus_one();
							//the_game.show_winner(p1,led_player_1);
						}
						else if (the_game.get_statusled_time() < time_last_hit_p2) //player 2 also reacts correct
						{
							if (time_last_hit_p1 < time_last_hit_p2)	//player 1 wins, because of faster reaction
							{
								the_game.set_player_led(led_player_1);
								p1.set_won_rounds_plus_one();
								//the_game.show_winner(p1, led_player_1);
							}
							else										//player 2 wins, because of faster reaction
							{
								the_game.set_player_led(led_player_2);
								p2.set_won_rounds_plus_one();
								//the_game.show_winner(p2, led_player_2);
							}
						}
					}
					else if (the_game.get_statusled_time() < time_last_hit_p2)	// player 2 pressed btn after 3 seconds, player 1 did not
					{
						the_game.set_player_led(led_player_2);
						p2.set_won_rounds_plus_one();
						//the_game.show_winner(p2, led_player_2);
					}

					else		// get the false start winner		
					{
						//std::cout << std::endl << "Someone started false!" << std::endl;

						if (btn_hit_p2 && btn_hit_p1)	//both started false
						{
							if (time_last_hit_p1 < time_last_hit_p2)	//player 1 started false earlier
							{
								the_game.set_player_led(led_player_2);
								p2.set_won_rounds_plus_one();
								//the_game.show_winner(p2, led_player_2);
							}
							else	//player 2 started false earlier
							{
								the_game.set_player_led(led_player_1);
								p1.set_won_rounds_plus_one();
								//the_game.show_winner(p1, led_player_1);
							}
						}
						else if (btn_hit_p1)	//only player 1 did a false start
						{
							the_game.set_player_led(led_player_2);
							p2.set_won_rounds_plus_one();
							//the_game.show_winner(p2, led_player_2);
						}
						else	//only player 2 did a false start
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
			if ((!the_game.get_active_round()) && ((the_game.get_time_next_round() - act_time) < 0))
			{
				//reset btn_hit's
				btn_hit_p1 = FALSE;
				btn_hit_p2 = FALSE;

				std::cout << "Next round started!" << std::endl;
				if(the_game.get_rounds() != the_game.get_allready_played_rounds())
					the_game.set_active_round(TRUE);
			
				the_game.set_round_time();
				the_game.calc_status_time();

				// turn all LEDs off
				led_player_1.set(false);
				led_player_2.set(false);
				led_status.set(false);
			}

			//wait for 3 seconds, so last round winner can be seen
			if((the_game.get_rounds() == the_game.get_allready_played_rounds()) && (the_game.get_time_next_round() - act_time) < 0)
			{
				// turn all LEDs off
				led_player_1.set(false);
				led_player_2.set(false);
				led_status.set(false);

				the_game.set_over_all_active(FALSE);
				std::cout << std::endl << "All rounds played!" << std::endl;
			}

			spy_btn_status(btn_player_1, btn_player_2);		//Would be better in a timer isr all 10ms but didn't found anything in "www" how to do! ;-(
			delay(20);
		}
	
		//determine final score
		//
	
		if (p1.get_won_rounds() >= (the_game.get_rounds() / 2 + 1))
		{
			std::cout << std::endl << "Congratulation " << p1.get_username() << ", you have won more than 50% of the game!";
			std::cout << std::endl;
		
			test::winner_led_flashing(led_player_1);
		}
		else if (p2.get_won_rounds() >= (the_game.get_rounds() / 2 + 1))
		{
			std::cout << std::endl << "Congratulation " << p2.get_username() << ", you have won more than 50% of the game!";
			std::cout << std::endl;

			test::winner_led_flashing(led_player_2);
		}
	
		std::cout << p1.get_username() << " has won " << p1.get_won_rounds() << " rounds."<< std::endl;
		std::cout << p2.get_username() << " has won " << p2.get_won_rounds() << " rounds." << std::endl;

		constexpr auto delay_before_quit = 2000;
		delay(delay_before_quit);
		test::play_with_leds(led_player_1, led_player_2, led_status);
	
	}
	catch(const std::out_of_range& e)
	{
		std::cout << "Out of range exception has been thrown" << std::endl;
		std::cerr << e.what() << std::endl;
	}
	catch(const std::logic_error& e)
	{
		std::cerr << std::endl << "An error occured: " << e.what();
	}
	catch(...)
	{
		std::cout << "Default Exception Handler" << std::endl;
	}

	return 0;
}


constexpr long debounce_time = 200000;

void isr_button_player_1()
{
	//get actual system time and convert it into us
	const auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	const auto int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	static int64_t last_int_time_btn;

	if (((int_time_btn - last_int_time_btn) > debounce_time) && (status_btn_p1))	//debounce button
	{
		//std::cout << std::endl << "Button 1 was pressed." << std::endl;
		if (!btn_hit_p1)	//not necessary? -> interrupt indicates change of button, so button was pressed
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
	const auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	const auto int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	static int64_t last_int_time_btn;

	if (((int_time_btn - last_int_time_btn) > debounce_time) && (status_btn_p2))
	{
		//std::cout << std::endl << "Button 2 was pressed." << std::endl;
		if (!btn_hit_p2)
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

nlohmann::json read_config(std::string file_name)
{
	nlohmann::json j_object;
	std::ifstream in_pinout(file_name);
	std::stringstream iss;

	iss << in_pinout.rdbuf();	//not sure about it, but i think it is just a safe way to read the input
	in_pinout.close();			//I had trouble with reading the json file, so I play a little bit around
	iss >> j_object;

	return j_object;
}

