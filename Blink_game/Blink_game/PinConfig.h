#pragma once
#include "Pin.h"
#include "Enums.h"
#include <istream>

namespace reaction_game
{
	class Pin_config
	{
	public:
		explicit Pin_config(std::istream& stream);

		Pin_config(pi_io::Pin p1_button, pi_io::Pull_up_down p1_pud, pi_io::Pin p1_led,
			pi_io::Pin p2_button, pi_io::Pull_up_down p2_pud, pi_io::Pin p2_led,
			pi_io::Pin reaction_led);

		pi_io::Pin p1_button() const;
		pi_io::Pull_up_down p1_pud() const;
		pi_io::Pin p1_led() const;
		pi_io::Pin p2_button() const;
		pi_io::Pull_up_down p2_pud() const;
		pi_io::Pin p2_led() const;
		pi_io::Pin reaction_led() const;

	private:
		pi_io::Pin p1_button_;
		pi_io::Pull_up_down p1_pud_;
		pi_io::Pin p1_led_;
		pi_io::Pin p2_button_;
		pi_io::Pull_up_down p2_pud_;
		pi_io::Pin p2_led_;
		pi_io::Pin reaction_led_;
	};
}
