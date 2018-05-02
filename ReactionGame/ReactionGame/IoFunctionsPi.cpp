#include "IoFunctionsPi.h"
#include <wiringPi.h>
#include "Enums.h"
#include <ostream>
#include <iostream>
#include <chrono>


namespace pi_io
{

	int pi_io::io_functions_pi::map_pud(e_pull_up_down pud)
	{
		return pud == e_pull_up_down::up ? PUD_UP :
			pud == e_pull_up_down::down ? PUD_DOWN :
			PUD_OFF;
	}

	int pi_io::io_functions_pi::map_edge(e_edge_type edge)
	{
		return  edge == e_edge_type::both ? INT_EDGE_BOTH :
			edge == e_edge_type::falling ? INT_EDGE_FALLING :
			edge == e_edge_type::rising ? INT_EDGE_RISING :
			INT_EDGE_SETUP;
	}
	int io_functions_pi::map_mode(e_mode mode)
	{
		return mode == e_mode::clk ? GPIO_CLOCK :
			mode == e_mode::out ? OUTPUT :
			PWM_OUTPUT;
	}

}





