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

#if 0
TEST(SampleTest, Foo) {} // class SampleTest_Foo_Test : public testing::Test {}
TEST(SampleTest, Goo) {} // class SampleTest_Goo_Test : public testing::Test {}

//              testing::Test
//                    |
//            -------------------
//            |                 |
//       SampleTest.Foo     SampleTest.Goo     


class SampleTest : public testing::Test {};
TEST_F(SampleTest, Foo) {}  // class SampleTest_Foo_Test : public SampleTest {};
TEST_F(SampleTest, Goo) {}  // class SampleTest_Goo_Test : public SampleTest {};

//              testing::Test
//                    |
//                SampleTest 
//                    |
//            -------------------
//            |                 |
//       SampleTest.Foo     SampleTest.Goo     
#endif

// 적용 방법
// 1) 명시적인 Test Suite class 를 만들어야 합니다.
class CalculatorTest : public testing::Test {
// public:
protected:
// - 자식 클래스로 만들어진 테스트케이스에 접근하기 위해서는 protected로 만들어야 합니다.
	Calculator* Create() { return new Calculator; }
};

// 2) TEST가 아닌 TEST_F를 통해 테스트케이스를 만들어야 합니다.
// TEST: 암묵적인 Test Suite 
// TEST_F: 명시적인 Test Suite
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




















