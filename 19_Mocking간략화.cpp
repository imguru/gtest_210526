

enum Level { INFO, WARN };

class Logger {
public:
	virtual ~Logger() {}

	virtual void Send(Level level, const char* dir, const char* filename, int line, const char* message) = 0;
	// virtual void Send(Level level, const char* dir, const char* filename, int line, const char* message) {}
};

class User {
public:
	void Process(Logger* logger) {
		logger->Send(INFO, "users", "process.log", 10, "hello");
	}
};

#include <gmock/gmock.h>

class MockLogger : public Logger {
public:
	void Send(Level level, const char* dir, const char* filename, int line, const char* message) override {
		Send(level, dir); // !!!!
	}

	MOCK_METHOD(void, Send, (Level level, const char* dir));
};

TEST(UserTest, Process) {
	MockLogger logger;
	User user;

	EXPECT_CALL(logger, Send(INFO, "users"));

	user.Process(&logger);
}

#if 0
class MockLogger : public Logger {
public:
	MOCK_METHOD(void, Send,
		(Level level, const char* dir, const char* filename, int line, const char* message), (override));
};

TEST(UserTest, Process) {
	MockLogger logger;
	User user;

	EXPECT_CALL(logger, Send(INFO, "users", "process.log", 10, "hello"));

	user.Process(&logger);
}
#endif








