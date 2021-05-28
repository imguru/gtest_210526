
#include <stdio.h>

class Calc {
public:
	virtual ~Calc() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};

void Calculate(Calc* p) {
	// printf("Add: %d\n", p->Add(10, 20));  // 30
	// printf("Sub: %d\n", p->Sub(30, 20));  // 10
	if (p->Add(10, 20) == 30) {
		printf("Sub: %d\n", p->Sub(30, 20));  // 10
	}
}

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));
};

// MOCK_METHOD
//  - EXPECT_CALL : 행위 기반 검증
//  - ON_CALL     : 결과 제어(Delegating)

int Add(int a, int b) { return a + b; }
struct AddFunctor {
	int operator()(int a, int b) const {
		return a + b;
	}
};

// ON_CALL - Stub / Fake
using testing::Return;
TEST(CalcTest, Calculate) {
	MockCalc mock;
	// 1) 함수 포인터
	// - ON_CALL(mock, Add).WillByDefault(&Add);
	// 2) 함수 객체
	// - ON_CALL(mock, Add).WillByDefault(AddFunctor());
	// 3) C++11 - Lambda
	// - ON_CALL(mock, Add).WillByDefault([](int a, int b) { return a + b; });
	// 4) Return
	ON_CALL(mock, Add).WillByDefault(Return(30));

	EXPECT_CALL(mock, Add);
	EXPECT_CALL(mock, Sub);

	Calculate(&mock);
}





