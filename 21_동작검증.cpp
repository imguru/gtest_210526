
#include <gmock/gmock.h>

// 행위 기반 검증(동작 검증)
// 1. 함수 호출 여부
// 2. 함수 호출 횟수 + 인자 검증
// 3. 함수 호출 순서

class User {
public:
	virtual ~User() {}

	virtual void Go(int x, int y) = 0;
};

class MockUser : public User {
public:
	MOCK_METHOD(void, Go, (int x, int y), (override));
};

void Sample1(User* p) {
	p->Go(10, 20);
	p->Go(20, 30);
}

// 1. 함수 호출 여부
//   : EXPECT_CALL
TEST(UserTest, Sample1) {
	MockUser mock;

	EXPECT_CALL(mock, Go(10, 20));
	EXPECT_CALL(mock, Go(20, 30));

	Sample1(&mock);
}

// 2. 함수 호출 횟수
//   : EXPECT_CALL(..).Times(...)
TEST(UserTest, Sample2) {
	MockUser mock;

	EXPECT_CALL(mock, Go).Times(2);

	Sample1(&mock);
}










