#include <wiringPi.h>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>		//for timing conditions

#include "digitalOutputPi.h"
#include "digitalInputPi.h"
#include "pi_gpio_headers.h"
#include "GameSetup.h"
#include "Player.h"


// cd projects/Blink1/bin/ARM/Debug/ --> Ordnerstruktur

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
// we have to use BCM numbering when initializing with wiringPiSetupSys
// when choosing a different pin number please use the BCM numbering, also
// update the Property Pages - Build Events - Remote Post-Build Event command 
// which uses gpio export for setup for wiringPiSetupSys
// MFA avoid #defines, use constexpr instead
#define	LED_GREEN	8		//left colum, second pin
#define LED_YELLOW	9		// MFA bad names - use something like player1_led_pin or so
#define LED_RED		7
#define BTN_1		15		//button on the left side --> on the side where the leds are
#define BTN_2		16		//button on the right side

auto sys_now = std::chrono::system_clock::now().time_since_epoch();
int64_t int_time_btn1 = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
int64_t last_int_time_btn1;
int64_t int_time_btn2 = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
int64_t last_int_time_btn2;

// MFA this should be booleans. with uint8_t, one might think that this is something that may have more values
uint8_t btn_hit_l, btn_hit_r; // MFA only one variable declaration per line

void init_gpio_out(DigitalOutputPi& out1, DigitalOutputPi& out2, DigitalOutputPi& out3);
void init_gpio_in(DigitalInputPi& in1, DigitalInputPi& in2);
void is_button1_on(); // MFA naming: is_button1_on makes me think that this checks if button1 is on, but it is an isr (interrupt service routine)
void is_button2_on();

int main(void)
{
	// generate output pins
	DigitalOutputPi out_r(LED_RED, false); // MFA bad naming: r,g,y does not help me - player1_led, player2_led and game_led or so would be better
	DigitalOutputPi out_y(LED_YELLOW, true);
	DigitalOutputPi out_g(LED_GREEN, false);

	// generate input pins
	DigitalInputPi btn_left(BTN_1); // MFA bad naming - prefer something like player1_button
	DigitalInputPi btn_right(BTN_2);

	init_gpio_out(out_g, out_y, out_r);
	init_gpio_in(btn_left, btn_right);

	// game menue
	// MFA general recommendation: move the variable declaration to where it is needed. the variable scope should always be as small as possible!
	Game_setup react_setup;
	std::string user_1, user_2; // MFA one variable per line, also move declaration down to get_username
	int rounds_to_go = 0, act_round = 0; // MFA one variable per line
	int old_round = 0;
	int num_win_1 = 0, num_loss_1 = 0;
	int num_win_2 = 0, num_loss_2 = 0;
	int64_t time_limit_3s = 0;

	// print user mask and get necassary inputs
	react_setup.print_setup_mask();
	user_1 = react_setup.get_username(1);
	user_2 = react_setup.get_username(2);
	rounds_to_go = react_setup.get_number_plays();

	//initialize Players
	Player player_1{ user_1 };
	Player player_2{ user_2 };

	//first get system time and than convert to time in microseconds;
	auto sys_time_now = std::chrono::system_clock::now().time_since_epoch(); // MFA you could work with durations and time points, would be easier to read
	int64_t time_start_us = std::chrono::duration_cast<std::chrono::microseconds>(sys_time_now).count();

	//while (true){
		do  // MFA avoid do-while loops, see Cpp core guideline ES.75
		{ // MFA avoid busy waiting!
			if((btn_hit_l == 1) && (btn_hit_r == 1))
			{ // MFA this block should be in a separate method, e.g. handle_tie(...)
				player_1.set_result_round(game_outcome::TIE);
				player_2.set_result_round(game_outcome::TIE);
				out_g.setDigitalOutput(true);
				out_r.setDigitalOutput(true);
				out_y.setDigitalOutput(false);
				btn_hit_l = 0;
				btn_hit_r = 0;
				act_round++;
			}
			else if(btn_hit_l)
			{ // MFA this block should be in a separate method, e.g. handle_player1_win(...)
				btn_hit_l = 0;
				player_1.set_result_round(game_outcome::WIN);
				player_2.set_result_round(game_outcome::LOSS);
				out_g.setDigitalOutput(true);
				out_r.setDigitalOutput(false);
				out_y.setDigitalOutput(false);
				act_round++;
			}
			else if(btn_hit_r)
			{ // MFA this block should be in a separate method, e.g. handle_player2_win(...)
				btn_hit_r = 0;
				player_2.set_result_round(game_outcome::WIN);
				player_1.set_result_round(game_outcome::LOSS);
				out_g.setDigitalOutput(false);
				out_r.setDigitalOutput(true);
				out_y.setDigitalOutput(false);
				act_round++;
			}

			if(old_round != act_round)
			{ // MFA this block should be in a separate method, e.g. finish_round(...)
				old_round = act_round;
				player_1.get_overall_reult(&num_win_1, &num_loss_1);
				player_2.get_overall_reult(&num_win_2, &num_loss_2);
				sys_time_now = std::chrono::system_clock::now().time_since_epoch();
				time_start_us = std::chrono::duration_cast<std::chrono::microseconds>(sys_time_now).count();

				std::cout << std::endl << "Player 1, here your statistic so far: ";
				std::cout << "#" << num_win_1 << " wins and #" << num_loss_1 << " losses";
				
				std::cout << std::endl << "Player 2, here your statistic so far: ";
				std::cout << "#" << num_win_2 << " wins and #" << num_loss_2 << " losses" << std::endl;
			}

			sys_time_now = std::chrono::system_clock::now().time_since_epoch();
			time_limit_3s = std::chrono::duration_cast<std::chrono::microseconds>(sys_time_now).count();
			if((time_limit_3s - time_start_us) > 3000000)
			{ // MFA you should probably break here, otherwise you'll wait forever
				out_g.setDigitalOutput(false);
				out_r.setDigitalOutput(false);
				out_y.setDigitalOutput(true);
			}
			
		} while (act_round != rounds_to_go);

		// MFA fancy LED blinkery is missing
		//std::cout << "Test while!" << std::endl;
		/*
		if(my_btn.getDigitalInput())
		{
			out_g.setDigitalOutput(true);
			out_y.setDigitalOutput(true);
			out_r.setDigitalOutput(true);
		}
		else if(opponent_btn.getDigitalInput())
		{
			out_g.setDigitalOutput(false);
			out_y.setDigitalOutput(false);
			out_r.setDigitalOutput(false);	
		}
		*/
	//}
	return 0;
}

void is_button1_on()
{
	//get actual system time and convert it into us
	sys_now = std::chrono::system_clock::now().time_since_epoch();
	int_time_btn1 = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	// MFA avoid magic constants like 500000. 
	if((int_time_btn1 - last_int_time_btn1) > 500000)	//debounce button
	{
		std::cout << std::endl << "Button 1 was pressed." << std::endl;
		btn_hit_l = 1;
	}
	last_int_time_btn1 = int_time_btn1;
}

void is_button2_on()
{
	sys_now = std::chrono::system_clock::now().time_since_epoch();
	int_time_btn2 = std::chrono::duration_cast<std::chrono::microseconds>(sys_now).count();
	// MFA avoid magic constants like 500000 - use named variables instead
	// MFA you could use chrono_literals here
	if ((int_time_btn2 - last_int_time_btn2) > 500000) // MFA you could operate with durations here, too! no duration casts needed
	{
		std::cout << std::endl << "Button 2 was pressed." << std::endl;
		btn_hit_r = 1; // MFA use true and false literals
	}
	last_int_time_btn2 = int_time_btn2;
}

void init_gpio_out(DigitalOutputPi& out1, DigitalOutputPi& out2, DigitalOutputPi& out3)
{
	// configure output pins
	out1.configDigitalOutput(LED_GREEN, driver_conf::HIGH_STRENGTH, output_ctr::SOFTWARE_CTR, pin_mode::OUT);
	out2.configDigitalOutput(LED_YELLOW, driver_conf::HIGH_STRENGTH, output_ctr::SOFTWARE_CTR, pin_mode::OUT);
	out3.configDigitalOutput(LED_RED, driver_conf::HIGH_STRENGTH, output_ctr::SOFTWARE_CTR, pin_mode::OUT);
}

void init_gpio_in(DigitalInputPi& in1, DigitalInputPi& in2)
{
	// conigure pull-down/pull-up resitor
	// Note: A problem apeared by pushing the one buttons. Both function has been called, so I 
	//		 played around with the settings and increased the debounce time. Now it is 
	//		 stable, but I would like to improve it further.
	//
	in1.configDigitalInput(BTN_1, pud_conf::PULL_UP);
	in2.configDigitalInput(BTN_2, pud_conf::PULL_DOWN);

	// configure input as interrupt sensitive
	in1.configInputAsInterrupt(BTN_1, trig_setup::SENSE_RISING_EDGE, &is_button1_on);
	in2.configInputAsInterrupt(BTN_2, trig_setup::SENSE_FALLING_EDGE, &is_button2_on);
}
