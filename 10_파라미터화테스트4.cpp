
// 데이터 셋이 파일에 정의되어 있습니다.
#include <string>
#include <vector>
#include <iostream>

#include <gtest/gtest.h>

class StringTest : public testing::TestWithParam<std::string> {
};

using testing::ValuesIn;

std::vector<std::string> LoadFromFile() {
	std::vector<std::string> v;
#if 0
	v.push_back("hello");
	v.push_back("world");
	v.push_back("show");
	v.push_back("me");
	v.push_back("the");
	v.push_back("money");
#endif
	// stdin - EOF: Ctrl + D
	//  - $ ./a.out < input.txt
	while (!std::cin.eof()) {
		std::string input;
		std::cin >> input;

		v.push_back(input);
	}
	
	return v;
}

INSTANTIATE_TEST_SUITE_P(StringValues, StringTest, 
	ValuesIn(LoadFromFile()));
	
TEST_P(StringTest, LoadTest) {
	std::string s = GetParam();
	printf("%s\n", s.c_str());
}
