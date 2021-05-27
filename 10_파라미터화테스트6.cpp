#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> {
};

using testing::Values;
// 값을 직접 나열해서 사용할 경우
using testing::ValuesIn;
// 값을 기존의 컨테이너(배열, 함수)를 통해 가져올 경우,
using testing::Combine;
// 값을 조합해서 사용할 때
//   TestWithParam<std::tuple<T1, T2>>
//   Combine(Values(T1...), ValuesIn(T2...));

using testing::Range;
// Range(0, 100)
//  : [0, 100)
// Range(0, 100, 10)

INSTANTIATE_TEST_SUITE_P(IntValues, SampleTest,
	Range(0, 100, 10));

TEST_P(SampleTest, Sample) {
	printf("%d\n", GetParam());
}
