
#include <stdio.h>

class Calc {
public:
	virtual ~Calc() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};

void Calculate(Calc* p) {
	// printf("%d\n", p->Add(10, 20));
	if (p->Add(10, 20) == 30) {
		printf("%d\n", p->Sub(30, 20));
	}
}

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));
};

// ON_CALL / EXPECT_CALL을 동시에 사용하고 있다면,
//  => EXPECT_CALL을 통해서 ON_CALL 역활을 대신할 수 있습니다.

// ON_CALL
//  - WillByDefault

// EXPECT_CALL
//  - WillOnce

using testing::Return;

int Calculate2(Calc* p) {
	printf("Add: %d\n", p->Add(10, 20));
	printf("Add: %d\n", p->Add(10, 20));
	printf("Add: %d\n", p->Add(10, 20));
	printf("Add: %d\n", p->Add(10, 20));
}

TEST(CalcTest, Calculate2) {
	MockCalc mock;

	EXPECT_CALL(mock, Add)
		.WillOnce(Return(100))
		.WillOnce(Return(200))
		.WillOnce(Return(300))
		.WillOnce(Return(400));

	Calculate2(&mock);
}


TEST(CalcTest, Calculate) {
	MockCalc mock;

	EXPECT_CALL(mock, Add)
		.WillOnce(Return(30));

	EXPECT_CALL(mock, Sub)
		.WillOnce(Return(10000));

	Calculate(&mock);
}
#if 0
TEST(CalcTest, Calculate) {
	MockCalc mock;
	ON_CALL(mock, Add).WillByDefault(Return(30));

	EXPECT_CALL(mock, Add);
	EXPECT_CALL(mock, Sub);

	Calculate(&mock);
}
#endif












