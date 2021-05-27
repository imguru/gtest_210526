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
		//	p->Write(level, message);
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

#include <gmock/gmock.h> // Google Mock(Google Test)

// MOCK_METHOD{인자개수}(메소드 이름, 메소드 타입);

class MockDLoggerTarget : public DLoggerTarget {
public:
	// void Write(Level level, const std::string& message) override
	MOCK_METHOD2(Write, void(Level level, const std::string& message));
};

// DLogger에 2개 이상 Target 등록하고,
// Write 수행하였을 때, 각 Target에 Write가 제대로 전달되는지 여부를 검증하고 싶다.
TEST(DLoggerTest, Write) {
	// Arrange
	DLogger logger;
	MockDLoggerTarget t1;
	MockDLoggerTarget t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);

	// EXPECT_CALL이 실제 함수 호출 보다 먼저 작성되어야 합니다.
	// Assert
	EXPECT_CALL(t1, Write(INFO, "test_message"));
	EXPECT_CALL(t2, Write(INFO, "test_message"));

	// Act
	logger.Write(INFO, "test_message");
}
