#pragma once
#include "Enums.h"
#include "PinPi.h"
#include <cstdint>

namespace pi_io
{
	class Io_functions_pi
	{
		public:
			static int map_pud(e_pull_up_down pud);
			static int map_edge(e_edge_type edge);
			static int map_mode(e_mode mode);
			static int map_pin(e_pin pin);
	};

	
}
