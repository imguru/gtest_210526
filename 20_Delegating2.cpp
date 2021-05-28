
#include <gmock/gmock.h>

class User {
public:
	virtual ~User() {}

	virtual void Pure(int n) = 0;
	virtual int Concreate(const char* str) {
		printf("User::Concreate\n");
		return 0;
	}
};

class MockUser : public User {
public:
	MOCK_METHOD(void, Pure, (int n), (override));
	MOCK_METHOD(int, Concreate, (const char*), (override));

	// 부모의 원래 기능을 이용하기 위해서는 별도의 함수를 제공해야 합니다.
	int UserConcreate(const char* str) {
		return User::Concreate(str);
	}
};

TEST(UserTest, Sample) {
	MockUser mock;
	ON_CALL(mock, Concreate).WillByDefault([&mock](const char* str) {
		// User::Concreate의 기능을 재사용하고 싶습니다.
		// - MOCK_METHOD한 메소드에 대해서 다시 호출할 수 없습니다.
		return mock.UserConcreate(str);
	});

	EXPECT_CALL(mock, Concreate);

	mock.Concreate("hello");
}
