#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame/Player.h"
/*
 * Note: Following methods has to be tested:
		
		Player(std::string name);					//is tested successfully
		std::string get_username() const;			//is tested successfully
		void set_won_rounds_plus_one();				//is tested successfully
		unsigned int get_won_rounds() const;		//is tested successfully
 */
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace reaction_game_test
{		
	TEST_CLASS(Player_test)	//info, which class is going to be tested.
	{
	public:
		
		TEST_METHOD(test_construction)	//Here, test will be done
		{
			pi_game::Player p1{ "Michael" };
			
			Assert::AreEqual("Michael", p1.get_username().c_str());

			//check, if initialization is zero
			//
			Assert::AreEqual(0, static_cast<int>(p1.get_won_rounds()));

			//check, if counting wins is successfully and correct
			//
			p1.set_won_rounds_plus_one();
			Assert::AreEqual(1, static_cast<int>(p1.get_won_rounds()));
		}
	};
}