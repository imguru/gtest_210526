class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	Calculator(double v) {}
};

//------------------
#include <gtest/gtest.h>

// Fixture 설치 방법
// 1. Delegate Setup(위임 설치)
//  : 픽스쳐 설치에 관한 코드를 '테스트 유틸리티 함수'를 통해 모듈화한다.

// TEST: 암묵적인 Test Suite 

// 적용 방법
// 1) 명시적인 Test Suite class 를 만들어야 합니다.
class CalculatorTest : public testing::Test {
public:
	Calculator* Create() { return new Calculator; }
};

// 2) TEST가 아닌 TEST_F를 통해 테스트케이스를 만들어야 합니다.
TEST_F(CalculatorTest, Plus_2Plus2_Displays4) {
	// Arrange
	Calculator* calc = Create();
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();
	// Assert
	ASSERT_EQ(4, calc->Display()) << "2+2 하였을 때";
}

#define SPEC printf

TEST_F(CalculatorTest, Plus) {
	SPEC("2 더하기 2를 하였을 때 4가 제대로 나오는지 검증한다.\n");
	// Arrange
	Calculator* calc = Create();
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();
	// Assert
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2+2 하였을 때, 결과값이 다릅니다.";
	}
}




















