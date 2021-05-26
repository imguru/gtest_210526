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

// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는 모든 것을 
//        테스트 픽스쳐라고 합니다.
//        픽스쳐를 구성하는 모든 로직 부분을 '픽스쳐 설치(Fixture Setup)'라고 합니다.

// Fixture 설치 방법
// 1. Inline Fixture Setup
//  : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//  ㄴ장점: 픽스쳐를 설치하는 과정과 검증의 로직이 테스트 함수 안에 존재하기 때문에
//          인과 관계를 쉽게 분석할 수 있습니다.
//    단점: 모든 테스트 코드 안에서 '코드 중복'이 발생한다.

TEST(CalculatorTest, Plus_2Plus2_Displays4) {
	// Arrange
	Calculator* calc = new Calculator;
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();
	// Assert
	ASSERT_EQ(4, calc->Display()) << "2+2 하였을 때";
}

#define SPEC printf

TEST(CalculatorTest, Plus) {
	SPEC("2 더하기 2를 하였을 때 4가 제대로 나오는지 검증한다.\n");
	// Arrange
	Calculator* calc = new Calculator;
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




















