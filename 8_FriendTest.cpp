
// SUT
class User {
private:
	int age;
public:
	User(): age(42) {}

	void NextYear() {
		age += 1;
	}

protected:
	int GetAge() const {
		return age;
	}
};

#include <gtest/gtest.h>

// protected
//  : 테스트를 통해 접간하고자 하는 메소드가 protected 인 경우
//  해결방법: 테스트 전용 하위 클래스
//    - 테스트를 목적으로 SUT의 하위 클래스를 만든다.
class TestUser : public User {
public:
	using User::GetAge;   // 부모의 protected를 자식이 public으로 변경한다.
};

TEST(UserTest, NextYear) {
	TestUser user;   // !!!!

	user.NextYear();

	EXPECT_EQ(43, user.GetAge());
}



#if 0
// public
TEST(UserTest, NextYear) {
	User user;

	user.NextYear();

	EXPECT_EQ(43, user.GetAge());
}
#endif
