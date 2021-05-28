#include <gmock/gmock.h>

struct Element {};

class Calc {
	int x;
public:
	virtual ~Calc() {}

	// 검증 대상 X
	virtual int Add(Element x) {
		printf("Add(Element)\n");
	}

	// 검증 대상 O
	virtual int Add(int times, Element x) {
		printf("Add(int, Element)\n");
	}
};

//--------
// 1. SUT가 상속 가능한 클래스에 의존하고 있다면, Google Mock을 통해 행위 기반 검증을 수행할 수 있습니다.
// 2. 행위 기반 검증 대상 메소드만 Mocking 하면 됩니다.

class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int times, Element x), (override));
	// 3. 동일한 이름을 가지는 오버로딩 함수를 가립니다.
	// using Calc::Add;
};

// EXPECT_CALL에서 사용자 정의 객체에 대한 인자 검증이 필요하다면,
// 연산자 재정의 함수를 제공해주어야 합니다.
static bool operator==(const Element& x, const Element& y) {
	return true;
}

void Process(Calc* p) {
	p->Add(Element{});
	p->Add(100, Element{});
}

TEST(CalcTest, Add) {
	MockCalc calc;

	EXPECT_CALL(calc, Add(10, Element{}));

	// calc.Add(10, Element{});
	// no matching function for call to ‘MockCalc::Add(Element)’
	// calc.Add(Element{});
	Process(&calc);
}




















