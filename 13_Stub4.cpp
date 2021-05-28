#include <string>

class Time {
public:
	virtual ~Time() {}
	
	virtual std::string GetCurrentTime() = 0;
};

class Clock : public Time {
public:
	std::string GetCurrentTime() override {
		return "14:47";
	}
};

class User {
	Time* time;
public:
	User(Time* t) : time(t) {}

	int Display() {
		std::string t = time->GetCurrentTime();
		if (t == "00:00")
			return 42;
		
		return 100;
	}
};

//----
#include <gmock/gmock.h>
// User의 Display를 호출하였을 때, 00:00분에 42를 반환하는지 검증하고 싶다. 

using testing::Return;
using testing::NiceMock;

class StubTime : public Time {
public:
	MOCK_METHOD(std::string, GetCurrentTime, (), (override));
};

TEST(UserTest, Display) {
	NiceMock<StubTime> clock;
	ON_CALL(clock, GetCurrentTime).WillByDefault(Return("00:00"));
	User user(&clock);

	EXPECT_EQ(user.Display(), 42);
}
