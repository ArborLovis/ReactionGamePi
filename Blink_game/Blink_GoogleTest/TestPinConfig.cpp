#include "pch.h"

#include "../Blink_game/PinConfig.h"

TEST(PinConfig, ReadValidConfig) {
	std::stringstream config;
	std::string config_text{ "{ \"p1_led\": 10, \"p1_button\": 11,\"p2_led\": 12, \"p2_button\": 13,\"state\": 14 }" };
	config << config_text;

	reaction_game::Pin_config cfg{ config };
	EXPECT_EQ(10, bcm_number(cfg.p1_led()));
	EXPECT_EQ(12, bcm_number(cfg.p2_led()));
	EXPECT_EQ(11, bcm_number(cfg.p1_button()));
	EXPECT_EQ(13, bcm_number(cfg.p2_button()));
	EXPECT_EQ(14, bcm_number(cfg.reaction_led()));
}