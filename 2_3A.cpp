
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
// 1. Arrange(Given): 객체를 생성하고, 필요한 경우 설정하고 준비한다.
// 2. Act(When): 객체에 작용을 가한다.
// 3. Assert(Then): 기대하는 바를 단언한다.
//
// TDD vs BDD(Behavior Driven Development)
// 1) 용어적인 차이
//   : 가독성
// 2) 행위 기반 검증

// 테스트 코드 품질
// 1) 가독성
// 2) 유지보수성
//   : 테스트 케이스 블록 안에서 제어 구문(조건문, 반복문, 예외처리 등)의 발생을 최소화 해야 합니다.
// 3) 신뢰성

// CalculatorTest.Plus
// ex) 테스트대상메소드_시나리오_결과
// TEST(CalculatorTest, Plus) {
TEST(CalculatorTest, Plus_2Plus2_Displays4) {
	// Arrange
	Calculator* calc = new Calculator;
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();
	// Assert
	// GoogleTest - 단언 매크로
	// - ASSERT_EQ / NE / LT / GT / LE / GE ...
	ASSERT_EQ(4, calc->Display()) << "2+2 하였을 때";
#if 0
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2+2 하였을 때, 결과값이 다릅니다.";
	}
#endif
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




















