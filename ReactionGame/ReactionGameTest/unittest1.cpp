#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame/Player.h"
#include "../ReactionGame/Enums.h"
#include "../ReactionGame/Manage_Io.h"
#include "../ReactionGame/Files_Patrick_old/GameSetup.h"
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
	//
	// ############# CLASS PLAYER TEST #############
	//
	TEST_CLASS(Player_test)	//info, which class is going to be tested.
	{
	public:
		
		TEST_METHOD(test_player_handling)	//Here, test will be done
		{
			Logger::WriteMessage("*** player creation test started ***");
			bool exception_thrown = false;
			try
			{
				// player has to be created over console input
				//
				pi_game::Player p1{ "Michael" };
			}
			catch (std::logic_error& err)
			{
				static auto message = err.what();
				exception_thrown = true;
			}

			Assert::IsTrue(exception_thrown);// << "Exception";
			
			Logger::WriteMessage("*** woring with player test started ***");

			// not the finest art, but just for testing
			// Note to me: Problem with add_user, this makes create_player useless
			//
			Game_setup user_handler;
			user_handler.add_user("Patrick");
			pi_game::Player p1{ "Patrick" };

			Assert::AreEqual("Patrick", p1.get_username().c_str());
			Assert::AreNotEqual("Michael", p1.get_username().c_str());

			//check, if initialization is zero
			//
			Assert::AreEqual(0, static_cast<int>(p1.get_won_rounds()));

			//check, if counting wins is successfully and correct
			//
			p1.set_won_rounds_plus_one();
			Assert::AreEqual(1, static_cast<int>(p1.get_won_rounds()));
		}
	};

	TEST_CLASS(Player_test_part2)	//info, which class is going to be tested.
	{
	public:

		TEST_METHOD(test_player_handling_part2)	//Here, test will be done
		{
			Logger::WriteMessage("*** player copying test started ***");

			Game_setup user_hanler;
			user_hanler.add_user("Patrick the Second");
			pi_game::Player p2{ "Patrick the Second" };

			//check, if counting wins is successfully and correct
			//
			p2.set_won_rounds_plus_one();
			Assert::AreEqual(1, static_cast<int>(p2.get_won_rounds()));			

			// test, if player is copyable
			//

			pi_game::Player p1 = p2;
			Assert::AreEqual("Patrick the Second", p1.get_username().c_str());

			//check, if initialization is zero
			//
			Assert::AreEqual(1, static_cast<int>(p1.get_won_rounds()));

			//check, if counting wins is successfully and correct
			//
			p1.set_won_rounds_plus_one();
			Assert::AreEqual(2, static_cast<int>(p1.get_won_rounds()));
		}
	};

	//
	// ############# CLASS MANAGE IO #############
	//
	TEST_CLASS(Manage_io_test)
	{
	public:
		TEST_METHOD(test_io_manager)
		{
			Logger::WriteMessage("*** pin reservation test started ***");
			pi_io::Manage_io pin_manager;

			//check, if pin is registered
			//
			pi_io::Manage_io::register_pin_as_used(pi_io::Pin::bcm_0);
			Assert::IsTrue(pin_manager.check_pin_in_use(pi_io::Pin::bcm_0));	//used
			Assert::IsFalse(pin_manager.check_pin_in_use(pi_io::Pin::bcm_1));	//not used

			// check exception for invalid pin handlig
			//
			bool throw_exception = false;

			try
			{
				Logger::WriteMessage("*** invalid pin number test started ***");
				pi_io::Manage_io::request_pin(-10);
			}
			catch (const std::logic_error& err)
			{
				const auto err_text = err.what();
				throw_exception = true;
				Assert::AreEqual("Pin Nr. does not exist!", err_text);
				Assert::AreNotEqual("Pin is allready in use!", err_text);	//redundant
			}

			Assert::IsTrue(throw_exception);	// pin number can not have any value

			throw_exception = false;
			try
			{
				Logger::WriteMessage("*** multiple mapping test started ***");
				pi_io::Manage_io::request_pin(8);
				pi_io::Manage_io::request_pin(8);
			}
			catch (const std::logic_error& err)
			{
				const auto err_text = err.what();
				throw_exception = true;
				Assert::AreNotEqual("Pin Nr. does not exist!", err_text);
				Assert::AreEqual("Pin is allready in use!", err_text);		//redundant
			}

			Assert::IsTrue(throw_exception);	// pin can not be registered twice
		}
	};
}