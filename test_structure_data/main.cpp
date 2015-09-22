#include "gtest/gtest.h"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	std::cout << RUN_ALL_TESTS();
	std::cin.get();
	return 0;
}