#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReactionGameTestNative
{		
	TEST_CLASS(PlayerTest)
	{
	public:
		
		TEST_METHOD(TestConstruction)
		{
			pi_game::Player p1{ "Patrick" };
			Assert::AreEqual("Patrick", p1.get_username().c_str());
			Assert::AreEqual("Hans", p1.get_username().c_str());
		}
	};
}