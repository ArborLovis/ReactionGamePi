#include <wiringPi.h>
#include <iostream>
#include <sstream>
#include <chrono>		//for timing conditions

#include "DigitalInputPi.h"
#include "PinPi.h"
#include "DigitalOutputPi.h"
#include "ReactionGame.h"
#include "TestFunctions.h"


void isr_button1();
void isr_button2();
void spy_btn_status(pi_io::digital_input_pi btn1, pi_io::digital_input_pi btn2);

// Global variables for button Player1 and Player2
bool btn_hit_p1;
bool status_btn1;
int64_t time_last_hit_p1;

bool btn_hit_p2;
bool status_btn2;
int64_t time_last_hit_p2;



int main(void)
{
	// Setup Wiring PI ones
	wiringPiSetup();

	// IO Config

	using namespace pi_io;

	// setup Input Button	
	const digital_input_pi btn_player_1{ pi_io::e_pin::bcm_0, pi_io::e_pull_up_down::up, pi_io::e_edge_type::falling, &isr_button1 };
	const digital_input_pi btn_player_2{ pi_io::e_pin::bcm_1, pi_io::e_pull_up_down::up, pi_io::e_edge_type::falling, &isr_button2 };

	// setup Output LED's
	const digital_output_pi led_player_1{ pi_io::e_pin::bcm_2, pi_io::e_mode::out };
	const digital_output_pi led_player_2{ pi_io::e_pin::bcm_3, pi_io::e_mode::out };
	const digital_output_pi led_status{ pi_io::e_pin::bcm_4, pi_io::e_mode::out };

	// setup player
	std::string player_name;
	std::string player_name_1;
	std::string player_name_2;

	for(auto player_number = 1; player_number<3; player_number++)
	{
		std::cout << "Player " << player_number << ", enter your name: ";
		std::cin >> player_name;

		if(player_name == player_name_1)
		{
			player_number--;
			std::cout << "Name allready in use, please type an outher one!" << std::endl;
		}

		switch (player_number)
		{
			case 1: player_name_1 = player_name; break;
			case 2: player_name_2 = player_name; break;
			default:break;
		}
	}

	pi_game::player p1{ player_name_1 };
	pi_game::player p2{ player_name_2 };


	//auto p1 = pi_game::create_player(1);
	//auto p2 = pi_game::create_player(2);
	

	// setup Reaction Game
	pi_game::reaction_game the_game{};
	std::cout << "We play "<< the_game.get_rounds() << " rounds!" << std::endl;

	// set all Led's off
	led_player_1.set_digital_output_false();
	led_player_2.set_digital_output_false();
	led_status.set_digital_output_false();

	// local vars
	auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	auto act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();






	#define ONE_SECOND 1000				// for millisecond delay
	#define THREE_SECOND 3000000		// for microsecond calc time
	// clear buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

	// start game
	std::cout << "If you are ready, press Enter to start the game in 3 seconds!";
	getchar();
	std::cout << "... 3" << std::endl;
	delay(ONE_SECOND);
	std::cout << "... 2" << std::endl;
	delay(ONE_SECOND);
	std::cout << "... 1" << std::endl;
	delay(ONE_SECOND);

	the_game.set_allready_played_rounds(0);
	the_game.set_round_time();
	the_game.calc_status_time();
	the_game.set_over_all_active(TRUE);
	the_game.set_active_round(TRUE);

	std::cout << "Game started!" << std::endl;
	while (the_game.get_over_all_active())
	{

		sys_now = std::chrono::system_clock::now().time_since_epoch();
		act_time = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();

		if (the_game.get_active_round())
		{
			// set status led
			if ((the_game.get_statusled_time() - act_time) < 0)
			{
				led_status.set_digital_output_true();
			}

			// terminate the game after 3 secound inactivity
			if(act_time - the_game.get_statusled_time() > THREE_SECOND)
			{
				the_game.set_active_round(FALSE);
				the_game.set_allready_played_rounds(the_game.get_rounds());
				std::cout << "Game derminated!" << std::endl;
			}

			//determine the winner !
			if (btn_hit_p1 || btn_hit_p2)
			{
				//set game status to FALSE and calc the winner led runtime
				the_game.set_active_round(FALSE);
				the_game.set_time_next_round(act_time + THREE_SECOND);
				the_game.set_allready_played_rounds_plus_one();


				if (the_game.get_statusled_time() < time_last_hit_p1)
				{
					if (!btn_hit_p2)
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
		if (!the_game.get_active_round() && ((the_game.get_time_next_round() - act_time) < 0))
		{
			//reset btn_hit's
			btn_hit_p1 = FALSE;
			btn_hit_p2 = FALSE;

			std::cout << "Next round started!" << std::endl;
			the_game.set_active_round(TRUE);
			the_game.set_round_time();
			the_game.calc_status_time();

			// set all Led's off
			led_player_1.set_digital_output_false();
			led_player_2.set_digital_output_false();
			led_status.set_digital_output_false();
		}

		if(the_game.get_rounds() == the_game.get_allready_played_rounds())
		{
			// set all Led's off
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

	std::cout << p1.get_username() << " has won " << p1.get_won_rounds() << " rounds."<< std::endl;
	std::cout << p2.get_username() << " has won " << p2.get_won_rounds() << " rounds." << std::endl;

	test::play_with_leds(led_player_1, led_player_2, led_status);








	return 0;
}










#define BOUNCE_TIME 200000

void isr_button1()
{
	auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	auto int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	static int64_t last_int_time_btn;

	//get actual system time and convert it into us
	sys_now = std::chrono::system_clock::now().time_since_epoch();
	int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();

	if (((int_time_btn - last_int_time_btn) > BOUNCE_TIME) && (status_btn1))	//debounce button
	{
		//std::cout << std::endl << "Button 1 was pressed." << std::endl;
		if (!btn_hit_p1)
		{
			btn_hit_p1 = TRUE;
			time_last_hit_p1 = int_time_btn;
		}

		last_int_time_btn = int_time_btn;
	}
}


void isr_button2()
{
	auto sys_now = std::chrono::system_clock::now().time_since_epoch();
	auto int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	static int64_t last_int_time_btn;

	sys_now = std::chrono::system_clock::now().time_since_epoch();
	int_time_btn = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();

	if (((int_time_btn - last_int_time_btn) > BOUNCE_TIME) && (status_btn2))
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

void spy_btn_status(pi_io::digital_input_pi btn1, pi_io::digital_input_pi btn2)
{
	static bool status_last_btn1 = HIGH;
	static bool status_last_btn2 = HIGH;

	const auto act_status_btn1 = btn1.get_digital_input();
	const auto act_status_btn2 = btn2.get_digital_input();



	if(act_status_btn1 == status_last_btn1)
	{
		status_btn1 = status_last_btn1;
	}

	if (act_status_btn2 == status_last_btn2)
	{
		status_btn2 = status_last_btn2;
	}

	status_last_btn1 = act_status_btn1;
	status_last_btn2 = act_status_btn2;
}


