#pragma once

namespace pi_io {

	enum class e_state { low = 0, high = 1 };

	enum class e_mode { out = 0, pwm = 1, clk = 2 };

	enum class e_edge_type { falling, rising, both, setup };

	enum class e_pull_up_down { off = 0, down = 1, up = 2 };

}