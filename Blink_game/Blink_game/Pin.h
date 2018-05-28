#pragma once
#include <type_traits>

namespace pi_io {

	enum class Pin
	{
		bcm_0 = 0,
		wiring_pi_30 = 0,
		pysical_27 = 0,

		bcm_1 = 1,
		wiring_pi_31 = 1,
		pysical_28 = 1,

		bcm_2 = 2,
		wiring_pi_8 = 2,
		pysical_3 = 2,

		bcm_3 = 3,
		wiring_pi_9 = 3,
		pysical_5 = 3,

		bcm_4 = 4,
		wiring_pi_7 = 4,
		pysical_7 = 4,

		bcm_5 = 5,
		wiring_pi_21 = 5,
		pysical_29 = 5,

		bcm_6 = 6,
		wiring_pi_22 = 6,
		pysical_31 = 6,

		bcm_7 = 7,
		wiring_pi_11 = 7,
		pysical_26 = 7,

		bcm_8 = 8,
		wiring_pi_10 = 8,
		pysical_24 = 8,

		bcm_9 = 9,
		wiring_pi_13 = 9,
		pysical_21 = 9,

		bcm_10 = 10,
		wiring_pi_12 = 10,
		pysical_19 = 10,

		bcm_11 = 11,
		wiring_pi_14 = 11,
		pysical_23 = 11,

		bcm_12 = 12,
		wiring_pi_26 = 12,
		pysical_32 = 12,

		bcm_13 = 13,
		wiring_pi_23 = 13,
		pysical_33 = 13,

		bcm_14 = 14,
		wiring_pi_15 = 14,
		pysical_8 = 14,

		bcm_15 = 15,
		wiring_pi_16 = 15,
		pysical_10 = 15,

		bcm_16 = 16,
		wiring_pi_27 = 16,
		pysical_36 = 16,

		bcm_17 = 17,
		wiring_pi_0 = 17,
		pysical_11 = 17,

		bcm_18 = 18,
		wiring_pi_1 = 18,
		pysical_12 = 18,

		bcm_19 = 19,
		wiring_pi_24 = 19,
		pysical_35 = 19,

		bcm_20 = 20,
		wiring_pi_28 = 20,
		pysical_38 = 20,

		bcm_21 = 21,
		wiring_pi_29 = 21,
		pysical_40 = 21,

		bcm_22 = 22,
		wiring_pi_3 = 22,
		pysical_15 = 22,

		bcm_23 = 23,
		wiring_pi_4 = 23,
		pysical_16 = 23,

		bcm_24 = 24,
		wiring_pi_5 = 24,
		pysical_18 = 24,

		bcm_25 = 25,
		wiring_pi_6 = 25,
		pysical_22 = 25,

		bcm_26 = 26,
		wiring_pi_25 = 26,
		pysical_37 = 26,

		bcm_27 = 27,
		wiring_pi_2 = 27,
		pysical_13 = 27,
	};

	constexpr int mappings[28][2] = {
		{ 30, 27 },
		{ 31, 28 },
		{ 8, 3 },
		{ 9, 5 },
		{ 7, 7 },
		{ 21, 29 },
		{ 22, 31 },
		{ 11, 26 },
		{ 10, 24 },
		{ 13, 21 },
		{ 12, 19 },
		{ 14, 23 },
		{ 26, 32 },
		{ 23, 33 },
		{ 15, 8 },
		{ 16, 10 },
		{ 27, 36 },
		{ 0, 11 },
		{ 1, 12 },
		{ 24, 35 },
		{ 28, 38 },
		{ 29, 40 },
		{ 3, 15 },
		{ 4, 16 },
		{ 5, 18 },
		{ 6, 22 },
		{ 25, 37 },
		{ 2, 13}
	};

	template<typename T>
	constexpr auto to_underlying(T t) noexcept
	{
		return static_cast<std::underlying_type_t<T>>(t);
	}

	constexpr int bcm_number(Pin pin) noexcept
	{
		return to_underlying(pin);
	}

	constexpr int wiring_pi_number(Pin pin)
	{
		return mappings[to_underlying(pin)][0];
	}

	constexpr int physical_number(Pin pin)
	{
		return mappings[to_underlying(pin)][1];
	}

}
