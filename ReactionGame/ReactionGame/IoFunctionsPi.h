#pragma once
#include "Enums.h"
#include "PinPi.h"

namespace pi_io
{
	int map_pud(Pull_up_down pud);
	int map_edge(Edge_type edge);
	int map_mode(Mode mode);
	int map_pin(Pin pin);
	Pin map_pin_numbers(const int pin_num);
}
