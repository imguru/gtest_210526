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

// Fixture 설치 방법
// 3. Implicit Set up/Tear down(암묵적 설치/해체)
//  => xUnit Test Framework가 제공하는 기능입니다.
//  : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp() 함수에서 생성한다.
//   - 명시적인 테스트 스위트 클래스가 필요합니다.
//   장점: 테스트 코드 중복을 제거하고, 꼭 필요하지 않은 상호작용을 캡슐화할 수 있다.
//   단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에, 테스트 함수만으로 테스트 코드를
//         이해하기 어려울 수 있다.

// xUnit Test Pattern - Test case 구성 방법.
//  => Four Phase Test Pattern(4단계 테스트 패턴)
//  1단계: 테스트 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해서 필요한 것을 집어넣는 작업을 수행한다. - SetUp()
//  2단계: SUT와 상호작용한다.    - TestCase
//  3단계: 기대 결과를 확인한다.  - TestCase
//  4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓는다. - TearDown()

// xUnit Test Framework가 테스트를 수행하는 흐름
#if 0
// 신선한 픽스쳐 전략
CalculatorTest* ts = new CalculatorTest;
ts->SetUp();
ts->Foo();
ts->TearDown();
delete ts;

CalculatorTest* ts = new CalculatorTest;
ts->SetUp();
ts->Goo();
ts->TearDown();
delete ts;
#endif

class CalculatorTest : public testing::Test {
protected:
	CalculatorTest() { printf("CalculatorTest()\n"); }
	~CalculatorTest() { printf("~CalculatorTest()\n"); }

	// virtual void SetUp() {}
	// void SetUp() {}
	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	void TearDown() override {
		printf("TearDown()\n");
		delete calc;
	}

	Calculator* calc;
};

TEST_F(CalculatorTest, Plus_2Plus2_Displays4) {
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();
	// Assert
	ASSERT_EQ(4, calc->Display()) << "2+2 하였을 때";

	// 위의 단언문이 실패할 경우, 이후의 코드는 수행되지 않습니다.
	// printf("Calc 해제\n");
	// delete calc;
}

#define SPEC printf

TEST_F(CalculatorTest, Plus) {
	SPEC("2 더하기 2를 하였을 때 4가 제대로 나오는지 검증한다.\n");
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




















