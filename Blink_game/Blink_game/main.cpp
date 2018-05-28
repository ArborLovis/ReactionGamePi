// The Reaction Game
//
// A simple reaction game between two players, designed for Raspberry Pis.
//
// Version 1.0
//
// Copyright 2018, Michael Faschinger <michivo@gmail.com>
//
// MIT LICENSE
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
// and associated documentation files(the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, publish, distribute, 
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all copies or 
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "Pin.h"

#include "Player.h"
#include "PinConfig.h"
#include "ReactionGame.h"

#include <iostream>
#include <fstream>

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------
int main(void)
{
	using namespace pi_io;

	const auto p1 = reaction_game::create_player(1);
	const auto p2 = reaction_game::create_player(2);

	std::cout << "How many rounds do you want to play? ";
	int count = 0;

	const auto max_num_rounds = 100;
	const auto min_num_rounds = 1;

	if (!(std::cin >> count) || count < min_num_rounds || count > max_num_rounds)
	{
		std::cout << "Invalid number of rounds, enter a number between "
			<< min_num_rounds << " and " << max_num_rounds << std::endl;
		return 0;
	}

	std::ifstream pin_file{ "pins.json" };
	const reaction_game::Pin_config cfg{ pin_file };

	reaction_game::Reaction_game game{ p1, p2, cfg, count };
	game.play();

	return 0;
}
