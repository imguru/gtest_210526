
// SUT: System Under Test
//  => 테스트 대상 시스템
//  => Class Under Test / Code Under Test
class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

//------------------
#include <gtest/gtest.h>

// TestSuiteName
//  : 테스트 스위트 이름은 테스트 대상 클래스의 마지막에 Test/Spec를 붙인 이름을 사용합니다.
//  Calculator -> CalculatorTest / CalculatorSpec

// 3A
// 1. Arrange: 객체를 생성하고, 필요한 경우 설정하고 준비한다.
// 2. Act: 객체에 작용을 가한다.
// 3. Assert: 기대하는 바를 단언한다.

// CalculatorTest.Plus
TEST(CalculatorTest, Plus) {
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




















