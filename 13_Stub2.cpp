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
#include <gtest/gtest.h>
// User의 Display를 호출하였을 때, 00:00분에 42를 반환하는지 검증하고 싶다. 

class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, Display) {
	// Clock clock;
	StubTime clock;
	User user(&clock);

	EXPECT_EQ(user.Display(), 42);
}
