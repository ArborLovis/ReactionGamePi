#pragma once

namespace pi_io {
	
	enum class State { low = 0, high = 1 };

	enum class Mode { in = 0, out = 1, pwm = 2 };

	enum class Edge_type { falling, rising, both, setup };

	enum class Pull_up_down { off = 0, down = 1, up = 2 };

}