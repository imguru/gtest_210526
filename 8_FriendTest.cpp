
// SUT
// User.h
#if 0
class User {
private:
	int age;
public:
	User(): age(42) {}

	void NextYear() {
		age += 1;
	}

// protected:
private:
	int GetAge() const {
		return age;
	}
};
#endif

// 절대 사용하지 마세요.
// ----------
#if 0
#define private public
#define class struct
#include "User.h"
#undef private
#undef class
#endif
// ----------

#include <gtest/gtest.h>
#include "User."
// private
//  : FRIEND_TEST를 통해 접근 가능합니다.
//  => 문제점: SUT가 Google Test에 대한 의존성이 생성됩니다.
//
//  => 설계적으로 변경될 필요가 있습니다.
//  - private 메소드가 테스트되어야 하는가?
//   : 테스트 코드를 통해서 수행되지 않는 private가 메소드가 있다면, 
//     외부에서 접근 가능하도록 변경하는 것이 좋습니다.
//     "로버트 C 마틴": private 메소드 용도
//         => public 메소드의 가독성을 높이기 위해 사용해야 한다.
//         => 테스트 되지 않은 private 메소드가 테스트 된 public 메소드보다 위험하다.
//
TEST(UserTest, NextYear) {
	User user;   

	user.NextYear();

	EXPECT_EQ(43, user.GetAge());
}
#if 0
// protected
//  : 테스트를 통해 접근하고자 하는 메소드가 protected 인 경우
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
#endif



#if 0
// public
TEST(UserTest, NextYear) {
	User user;

	user.NextYear();

	EXPECT_EQ(43, user.GetAge());
}
#endif
