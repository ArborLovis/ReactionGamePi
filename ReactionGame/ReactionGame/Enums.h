#pragma once

namespace pi_io {

	enum class State { low = 0, high = 1 };

	enum class Mode { out = 0, pwm = 1, clk = 2 };

	enum class Edge_type { falling, rising, both, setup };

	enum class Pull_up_down { off = 0, down = 1, up = 2 };

}