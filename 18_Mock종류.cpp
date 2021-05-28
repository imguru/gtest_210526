
class User {
public:
	virtual ~User() {}

	virtual void Go() = 0;
	virtual void Say() = 0;
};

void UseUser(User* p) {
	p->Go();
	p->Say();
}

#include <gmock/gmock.h>

#if 0
GMOCK WARNING:
Uninteresting mock function call - returning directly.
    Function call: Say()
#endif
// 원인: MOCK_METHOD한 메소드에 대해서 호출이 되었는데, 검증(EXPECT_CALL)을 하고 있지 않다.
// * Google Mock 종류 3가지
// 1. Naggy Mock(Default)
//  => 관심없는 호출에 대한 경고가 발생합니다.
//  => 테스트의 결과에는 영향이 없습니다.
// 2. Nice Mock
//  => 경고가 발생하지 않습니다.
// 3. Strict Mock
//  => 테스트가 실패합니다.
//  => 테스트의 통과 기준이 높아진다. => 비용 증가
class MockUser : public User {
public:
	MOCK_METHOD(void, Go, (), (override));
	MOCK_METHOD(void, Say, (), (override));
};

using testing::NiceMock;
using testing::StrictMock;

TEST(UserTest, UseUser) {
	// MockUser user;
	// NiceMock<MockUser> user;
	StrictMock<MockUser> user;

	EXPECT_CALL(user, Go);
	// EXPECT_CALL(user, Say);

	UseUser(&user);
}







