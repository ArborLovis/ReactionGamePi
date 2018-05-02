#pragma once
#include "DigitalOutputPi.h"


namespace test
{

	void play_with_leds(pi_io::digital_output_pi led_p1, pi_io::digital_output_pi led_p2, pi_io::digital_output_pi led_status);
}