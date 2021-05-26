
// main.cpp

// 1. GoogleTest의 헤더파일은 한개만 필요합니다.
#include <gtest/gtest.h>

// 2. main
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
