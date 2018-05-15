#include "IoFunctionsPi.h"
#include <wiringPi.h>
#include "Enums.h"


namespace pi_io
{

	int map_pud(Pull_up_down pud)
	{
		return pud == Pull_up_down::up ? PUD_UP :
			pud == Pull_up_down::down ? PUD_DOWN :
			PUD_OFF;
	}

	int map_edge(Edge_type edge)
	{
		return  edge == Edge_type::both ? INT_EDGE_BOTH :
			edge == Edge_type::falling ? INT_EDGE_FALLING :
			edge == Edge_type::rising ? INT_EDGE_RISING :
			INT_EDGE_SETUP;
	}
	int map_mode(Mode mode)
	{
		return mode == Mode::clk ? GPIO_CLOCK :
			mode == Mode::out ? OUTPUT :
			PWM_OUTPUT;
	}

	int map_pin(Pin pin)
	{
		return pin == Pin::bcm_0 ? 0 :
			pin == Pin::bcm_1 ? 1 :
			pin == Pin::bcm_2 ? 2 :
			pin == Pin::bcm_3 ? 3 :
			pin == Pin::bcm_4 ? 4 :
			pin == Pin::bcm_5 ? 5 :
			pin == Pin::bcm_6 ? 6 :
			pin == Pin::bcm_7 ? 7 :
			pin == Pin::bcm_8 ? 8 :
			pin == Pin::bcm_9 ? 9 :
			pin == Pin::bcm_10 ? 10 :
			pin == Pin::bcm_11 ? 11 :
			pin == Pin::bcm_12 ? 12 :
			pin == Pin::bcm_13 ? 13 :
			pin == Pin::bcm_14 ? 14 :
			pin == Pin::bcm_15 ? 15 :
			pin == Pin::bcm_16 ? 16 :
			pin == Pin::bcm_17 ? 17 :
			pin == Pin::bcm_18 ? 18 :
			pin == Pin::bcm_19 ? 19 :
			pin == Pin::bcm_20 ? 20 :
			pin == Pin::bcm_21 ? 21 :
			pin == Pin::bcm_22 ? 22 :
			pin == Pin::bcm_23 ? 23 :
			pin == Pin::bcm_24 ? 24 :
			pin == Pin::bcm_25 ? 25 :
			pin == Pin::bcm_26 ? 26 :
			27;
	}

	Pin map_pin_numbers(const int pin_num)
	{
		// return static_cast<Pin>(pin_num); // MFA could be solved in a one-liner
		switch (pin_num)
		{
		case 0:
			return Pin::bcm_17;
		case 1:
			return Pin::bcm_18;
		case 2:
			return Pin::bcm_27;
		case 3:
			return Pin::bcm_22;
		case 4:
			return Pin::bcm_23;
		case 5:
			return Pin::bcm_24;
		case 6:
			return Pin::bcm_25;
		case 7:
			return Pin::bcm_4;
		case 8:
			return Pin::bcm_2;
		case 9:
			return Pin::bcm_3;
		case 10:
			return Pin::bcm_8;
		case 11:
			return Pin::bcm_7;
		case 12:
			return Pin::bcm_10;
		case 13:
			return Pin::bcm_9;
		case 14:
			return Pin::bcm_11;
		case 15:
			return Pin::bcm_14;
		case 16:
			return Pin::bcm_15;
		case 21:
			return Pin::bcm_5;
		case 22:
			return Pin::bcm_6;
		case 23:
			return Pin::bcm_13;
		case 24:
			return Pin::bcm_19;
		case 25:
			return Pin::bcm_26;
		case 26:
			return Pin::bcm_12;
		case 27:
			return Pin::bcm_16;
		case 28:
			return Pin::bcm_20;
		case 29:
			return Pin::bcm_21;
		case 30:
			return Pin::bcm_0;
		case 31:
			return Pin::bcm_1;
		default:
			throw "No Pin match found!";
		}
	}
}





