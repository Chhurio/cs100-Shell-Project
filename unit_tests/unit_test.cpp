#include "gtest/gtest.h"


//INSERT ALL THE TEST FILES HERER 
#include "tests.hpp"


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
