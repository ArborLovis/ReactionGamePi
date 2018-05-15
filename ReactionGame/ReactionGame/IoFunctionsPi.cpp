#include "IoFunctionsPi.h"
#include <wiringPi.h>
#include "Enums.h"


namespace pi_io
{

	int pi_io::Io_functions_pi::map_pud(e_pull_up_down pud)
	{
		return pud == e_pull_up_down::up ? PUD_UP :
			pud == e_pull_up_down::down ? PUD_DOWN :
			PUD_OFF;
	}

	int pi_io::Io_functions_pi::map_edge(e_edge_type edge)
	{
		return  edge == e_edge_type::both ? INT_EDGE_BOTH :
			edge == e_edge_type::falling ? INT_EDGE_FALLING :
			edge == e_edge_type::rising ? INT_EDGE_RISING :
			INT_EDGE_SETUP;
	}
	int Io_functions_pi::map_mode(e_mode mode)
	{
		return mode == e_mode::clk ? GPIO_CLOCK :
			mode == e_mode::out ? OUTPUT :
			PWM_OUTPUT;
	}
	int Io_functions_pi::map_pin(e_pin pin)
	{
		return pin == e_pin::bcm_0 ? 0 :
			pin == e_pin::bcm_1 ? 1 :
			pin == e_pin::bcm_2 ? 2 :
			pin == e_pin::bcm_3 ? 3 :
			pin == e_pin::bcm_4 ? 4 :
			pin == e_pin::bcm_5 ? 5 :
			pin == e_pin::bcm_6 ? 6 :
			pin == e_pin::bcm_7 ? 7 :
			pin == e_pin::bcm_8 ? 8 :
			pin == e_pin::bcm_9 ? 9 :
			pin == e_pin::bcm_10 ? 10 :
			pin == e_pin::bcm_11 ? 11 :
			pin == e_pin::bcm_12 ? 12 :
			pin == e_pin::bcm_13 ? 13 :
			pin == e_pin::bcm_14 ? 14 :
			pin == e_pin::bcm_15 ? 15 :
			pin == e_pin::bcm_16 ? 16 :
			pin == e_pin::bcm_17 ? 17 :
			pin == e_pin::bcm_18 ? 18 :
			pin == e_pin::bcm_19 ? 19 :
			pin == e_pin::bcm_20 ? 20 :
			pin == e_pin::bcm_21 ? 21 :
			pin == e_pin::bcm_22 ? 22 :
			pin == e_pin::bcm_23 ? 23 :
			pin == e_pin::bcm_24 ? 24 :
			pin == e_pin::bcm_25 ? 25 :
			pin == e_pin::bcm_26 ? 26 :
			27;
	}
}





