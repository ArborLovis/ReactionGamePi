#include "TestFunctions.h"
#include <wiringPi.h>

#define DELAY_TIME 100

namespace test
{
	void play_with_leds(pi_io::digital_output_pi led_p1, pi_io::digital_output_pi led_p2, pi_io::digital_output_pi led_status)
	{
		

		for(auto i = 0; i < 10; i ++)
		{
			led_p1.set_digital_output_true();
			delay(DELAY_TIME);
			led_p1.set_digital_output_false();
			led_status.set_digital_output_true();
			delay(DELAY_TIME);
			led_status.set_digital_output_false();
			led_p2.set_digital_output_true();
			delay(DELAY_TIME);
			led_p2.set_digital_output_false();
			led_status.set_digital_output_true();
			delay(DELAY_TIME);
			led_status.set_digital_output_false();
		}		
	}	
}
