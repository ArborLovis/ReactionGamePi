#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReactionGameTest
{		
	TEST_CLASS(PlayerTest)
	{
	public:
		
		TEST_METHOD(TestConstruction)
		{
			// TODO: Testcode hier eingeben
			pi_game::Player p1{ "Michael" };
			Assert::AreEqual("Michael", p1.get_username().c_str());
		}

	};
}