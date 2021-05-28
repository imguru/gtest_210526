#include <string>
#include <vector>

#include "DLoggerTarget.h"
#if 0
enum Level {
	INFO, WARN, ERROR,
};

class DLoggerTarget {
public:
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};
#endif

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

#include <gmock/gmock.h> // Google Mock(Google Test)

#if 0
// $ ./googletest/googlemock/scripts/generator/gmock_gen.py DLoggerTarget.h
//  => 1.10 이후로는 위의 방법을 통해 Mocking 하지 않습니다.
class MockDLoggerTarget : public DLoggerTarget {
 public:
  MOCK_METHOD2(Write,
      void(Level level, const std::string& message));
};
#endif



// 1.10 이전
//  : MOCK_METHOD{인자개수}(메소드 이름, 메소드 타입);
// 1.10 이후
//  : MOCK_METHOD(반환타입, 이름, 인자정보, 한정자)
class MockDLoggerTarget : public DLoggerTarget {
public:
	// MOCK_METHOD2(Write, void(Level level, const std::string& message));
	
	// void Write(Level level, const std::string& message) override
	MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
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

// Test Double(테스트 대역)
//  - 4가지
//  1. Test Stub
//    - 특수한 상황을 시뮬레이션 한다.
//      협력 객체에 대해서는 원하는 결과를 주도록 한다.
//  2. Fake Object
//    - 가벼운 테스트 대역을 통해 검증되지 않은 로직을 검증한다.
//  3. Test Spy
//    - 관찰할 수 있는 부수효과가 존재하지 않는다.
//     => 목격한 일을 기록해두었다가, 테스트에서 검증할 수 있도록 하는 테스트 대역
//  4. Mock Object
//    - 관찰할 수 있는 부수효과가 존재하지 않는다.
//    => 모의 객체를 통해 행위 기반 검증을 수행한다.

// Mock Framework => Test double Framework
//                   : Google Mock을 통해 행위 기반 검증도 수행할 수 있지만, 
//                     Stub / Fake 등의 목적으로도 사용할 수 있습니다.











