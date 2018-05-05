#pragma once
// MFA very nice!
// Input
enum class trig_setup { SENSE_RISING_EDGE, SENSE_FALLING_EDGE, SENSE_BOTH_EDGES, SENSE_EDGE_SETUP };
enum class pud_conf {NONE, PULL_UP, PULL_DOWN};

// Output
enum class driver_conf { LOW_STRENGTH, HIGH_STRENGTH };
enum class output_ctr { HARDWARE_CTR, SOFTWARE_CTR };
enum class pin_mode {OUT, PWM_OUT, GPIO_CLK};

//enum class digital_val {LOW, HIGH};

//The Reaction Game
enum class game_outcome { WIN, LOSS, TIE };
