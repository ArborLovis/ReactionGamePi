#include "CppUnitTest.h"

#include "../Blink_game/PinConfig.h"
#include "../Blink_game/PiIoManager.h"

#include <sstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Blink_tests
{		
	TEST_CLASS(Test_config)
	{
	public:
		
		TEST_METHOD(parse_config)
		{
			std::stringstream config;
			std::string config_text{ "{ \"p1_led\": 10, \"p1_button\": 11,\"p2_led\": 12, \"p2_button\": 13,\"state\": 14 }" };
			config << config_text;

			reaction_game::Pin_config cfg{ config };
			Assert::AreEqual(10, bcm_number(cfg.p1_led()));
			Assert::AreEqual(12, bcm_number(cfg.p2_led()));
			Assert::AreEqual(11, bcm_number(cfg.p1_button()));
			Assert::AreEqual(13, bcm_number(cfg.p2_button()));
			Assert::AreEqual(14, bcm_number(cfg.reaction_led()));
		}

		TEST_METHOD(parse_invalid_config)
		{
			std::stringstream config;
			std::string config_text{ "{ \"p1_led\": 10, \"p1_button\": 11,\"p3_led\": 12, \"p2_button\": 13,\"state\": 14 }" };
			config << config_text;

			Assert::ExpectException<std::exception>([&]() {reaction_game::Pin_config cfg{ config }; });
		}

	};

	TEST_CLASS(Test_io_manager)
	{
	public:

		TEST_METHOD(setup_manager)
		{
			pi_io::Pi_io_manager::instance().register_input(pi_io::Pin::bcm_11, [](pi_io::Pin p) {});
			const auto val = pi_io::Pi_io_manager::instance().digital_read(pi_io::Pin::bcm_11);
			Assert::AreEqual(static_cast<int>(pi_io::State::low), static_cast<int>(val));
		}

	};
}