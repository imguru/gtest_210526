
bool Foo(int arg1, int arg2) {
	return arg1 > arg2;
}

///---------
#include <gtest/gtest.h>

struct Input {
	int arg1;
	int arg2;

	bool result;
};

class SampleTest : public testing::TestWithParam<Input> {
};

// Google Test는 객체에 대한 사용자 정의 출력을 직접 제공해주어야 합니다.
std::ostream& operator<<(std::ostream& os, const Input& input) {
	return os << "Input{arg1=" << input.arg1 << ", arg2=" << input.arg2 << "}";
}

using testing::Values;
INSTANTIATE_TEST_SUITE_P(InputValues, SampleTest,
	Values(Input{20, 10, true}, Input{30, 20, true}, Input{40, 30, true}, Input{50, 40, true}, Input{30, 50, false}));

TEST_P(SampleTest, Foo) {
	Input input = GetParam();
	// EXPECT_TRUE(Foo(input.arg1, input.arg2));
	EXPECT_EQ(input.result, Foo(input.arg1, input.arg2));
}
