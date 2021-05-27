
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR,
};

class DLoggerTarget {
public:
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("File 기록 - %d[%s]\n", level, message.c_str());
	}
};

class NetworkTarget : public DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("Network 기록 - %d[%s]\n", level, message.c_str());
	}
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* p : targets) {
			p->Write(level, message);
		}
	}
};

//-----
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>  // find

// Mock Object Pattern
//   의도: SUT의 함수를 호출하였을 때 발생하는 부수효과를 관찰할 수 없어서, 테스트되지 않은 
//         요구사항이 있다.
//   방법: 모의 객체(Mock Object)를 이용해서 "행위 기반 검증"을 수행한다.

//   행위 기반 검증(동작 검증)
//     - 객체에 작용을 가한후, 내부적으로 발생하는 함수의 호출 여부 / 횟수 / 순서를 통해 검증한다.
//   상태 기반 검증(상태 검증)
//     - 객체에 작용을 가한후, 내부적으로 발생하는 부수효과(값의 변경)을 통해 검증한다.

//   모의 객체(Mock Object)
//    - 내부적으로 발생하는 함수의 호출 여부 / 횟수 / 순서 등의 정보를 저장합니다.
//    => Mock Framework
//      Java: jMock, EasyMock, Mockito, Spock ...
//       C++: Google Mock

class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string concat(Level level, const std::string& message) const {
		static std::string levels[] = {
			"I", "W", "E",
		};
		return levels[level] + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		history.push_back(concat(level, message));
	}

	bool IsReceived(Level level, const std::string& message) const {
		return std::find(history.begin(), history.end(), concat(level, message)) != history.end();
	}
};

// DLogger에 2개 이상 Target 등록하고,
// Write 수행하였을 때, 각 Target에 Write가 제대로 전달되는지 여부를 검증하고 싶다.
TEST(DLoggerTest, Write) {
	DLogger logger;
	SpyTarget t1;
	SpyTarget t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);

	logger.Write(INFO, "test_message");

	EXPECT_TRUE(t1.IsReceived(INFO, "test_message"));
	EXPECT_TRUE(t2.IsReceived(INFO, "test_message"));
}


#if 0
int main() {
	DLogger logger;
	FileTarget t1;
	NetworkTarget t2;

	logger.AddTarget(&t1);
	logger.AddTarget(&t2);

	logger.Write(INFO, "test_message1");
	logger.Write(WARN, "test_message2");
}
#endif













