#include "TestFunctions.h"
#include <wiringPi.h>


namespace test
{
	void play_with_leds(pi_io::Digital_output_pi led_p1, pi_io::Digital_output_pi led_p2, pi_io::Digital_output_pi led_status)
	{
		constexpr int delay_time_100 = 100;
		for(auto i = 0; i < 10; i ++)
		{
			led_p1.set(true);
			delay(delay_time_100);
			led_p1.set(false);
			led_status.set(true);
			delay(delay_time_100);
			led_status.set(false);
			led_p2.set(true);
			delay(delay_time_100);
			led_p2.set(false);
			led_status.set(true);
			delay(delay_time_100);
			led_status.set(false);
		}		
	}
	void winner_led_flashing(pi_io::Digital_output_pi led)
	{
		constexpr auto delay_time_100 = 100;
		constexpr auto flash_time_c = 50;

		for(auto i=0;i<flash_time_c;i++)
		{
			led.set(true);
			delay(delay_time_100);
			led.set(false);
			delay(delay_time_100);
		}
	}

}
