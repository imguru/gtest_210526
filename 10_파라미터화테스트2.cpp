

bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0) 
			return false;
	}
	return true;
}

#include <gtest/gtest.h>

// 파라미터화 테스트 패턴(Parameterized Test Pattern)
// => xUnit Test Framework가 제공하는 기능입니다.
// 의도: 입력 데이터를 바꿔가며, 
//       반복 검사하는 데이터 중심의 테스트에서 코드 중복을 없앨 수 있습니다.

// 1. 테스트 스위트 클래스
//             기존: class PrimeTest : public testing::Test
// 파라미터화테스트: class PrimeTest : public testing::TestWithParm<InputType>
class PrimeTest : public testing::TestWithParam<int> {
protected:
};

// 2. 데이터셋 정의
using testing::ValuesIn;

static int data[] = { 2, 3, 5, 6, 7, 11, 13, 15, 17, 19, 23 };
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, 
	ValuesIn(data));

// 3. 테스트케이스
//      기존: TEST / TEST_F
//  파라미터: TEST_P  - GetParam()
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}









