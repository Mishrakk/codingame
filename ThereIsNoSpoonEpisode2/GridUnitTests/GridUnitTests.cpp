#include "pch.h"
#include "CppUnitTest.h"

#include "../ThereIsNoSpoonEpisode2/Node.h"
#include "../ThereIsNoSpoonEpisode2/Grid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GridUnitTests
{
	TEST_CLASS(GridUnitTests)
	{
	public:
		
		TEST_METHOD(Simplest)
		{
			vector<string> vec{"1.2", "...", "..1"};
			Grid grid(3, 3, vec);
			vector<string> representation = grid.get_grid_representation();
			Assert::AreEqual(vec[0], representation[0]);
			Assert::AreEqual(vec[1], representation[1]);
			Assert::AreEqual(vec[2], representation[2]);
			bool is_correct_solution = grid.solve();
			representation = grid.get_grid_representation();
			Assert::AreEqual(string("0.0"), representation[0]);
			Assert::AreEqual(string("..."), representation[1]);
			Assert::AreEqual(string("..0"), representation[2]);
			Assert::AreEqual(grid.is_solved(), true);
			Assert::AreEqual(true, is_correct_solution);
		}

		TEST_METHOD(Intermediate2)
		{
			vector<string> vec{ 
						"2..2.1.",
						".3..5.3",
						".2.1...",
						"2...2..",
						".1....2"
			};
			Grid grid(7, 5, vec);
			bool is_correct_solution = grid.solve();
			Assert::AreEqual(true, grid.is_solved());
			Assert::AreEqual((int)grid.moves.size(), 13);
			Assert::AreEqual(true, is_correct_solution);
		}


		TEST_METHOD(Intermediate3)
		{
			vector<string> vec{ "25.1", "47.4", "..1.", "3344" };
			Grid grid(4, 4, vec);
			bool is_correct_solution = grid.solve();
			Assert::AreEqual(true, grid.is_solved());
			Assert::AreEqual(true, is_correct_solution);
		}

		TEST_METHOD(MultipleSolutions1)
		{
			vector<string> vec{ "33", "33" };
			Grid grid(2, 2, vec);
			bool is_correct_solution = grid.solve();

			Assert::AreEqual(true, grid.is_solved());
			Assert::AreEqual((int)grid.moves.size(), 6);
			Assert::AreEqual(true, is_correct_solution);
		}
		TEST_METHOD(MultipleSolutions2)
		{
			vector<string> vec{ ".12..",
								".2421",
								"24442",
								"1242.",
								"..21." };
			Grid grid(5, 5, vec);
			bool is_correct_solution = grid.solve();

			Assert::AreEqual(true, grid.is_solved());
			Assert::AreEqual(true, is_correct_solution);
		}
		TEST_METHOD(Advanced2)
		{
			vector<string> vec{ "3.....1..",
								".2..4..21",
								".3.2..1..",
								"..2.5.3..",
								".3...3.3.",
								"......2..",
								"..2..3..3",
								".3..3.3..",
								"3......44" };
			Grid grid(9, 9, vec);
			bool is_correct_solution = grid.solve();

			Assert::AreEqual(true, grid.is_solved());
			Assert::AreEqual(true, is_correct_solution);
		}
	};
}
