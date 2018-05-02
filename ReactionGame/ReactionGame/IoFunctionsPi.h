#pragma once
#include "Enums.h"
#include <cstdint>

namespace pi_io
{
	class io_functions_pi
	{
		public:
			static int map_pud(e_pull_up_down pud);
			static int map_edge(e_edge_type edge);
			static int map_mode(e_mode mode);
	};

	
}
