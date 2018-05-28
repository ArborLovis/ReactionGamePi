#include "pch.h"
#include "../Blink_game/PiIoManager.h"
#include "../Blink_win32/winpi.h"

TEST(PiIoManager, TestOutput) {
	using io_mgr = pi_io::Pi_io_manager;

	const auto handle = io_mgr::instance().register_output(pi_io::Pin::bcm_10);
	io_mgr::instance().digital_write(handle, pi_io::State::high);

	auto& emulator{ get_emulator() };
	EXPECT_EQ(emulator.get_state(10), 1);
	EXPECT_EQ(io_mgr::instance().digital_read(pi_io::Pin::bcm_10), pi_io::State::high);

	io_mgr::instance().digital_write(handle, pi_io::State::low);
	EXPECT_EQ(emulator.get_state(10), 0);
	EXPECT_EQ(io_mgr::instance().digital_read(pi_io::Pin::bcm_10), pi_io::State::low);
}