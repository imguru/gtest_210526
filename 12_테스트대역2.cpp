// 12_테스트대역2.cpp
#include <string>

// Logger가 의존하는 FileSystem을 테스트 대역으로 교체할 수 있어야 합니다.
//  => 테스트 대역을 적용하기 위해서는 특별한 설계가 필요합니다.
//  => 느슨한 결합(약한 결합)

//  강한 결합: 협력 객체를 이용할 때, 구체적인 타입에 의존한다.
//  약한 결합: 협력 객체를 이용할 때, "인터페이스나 추상 클래스 타입"에 의존한다.
//           => 교체 가능하다.
//           => 직접 생성하면 안됩니다.
//              외부에서 생성해서 전달받아야 합니다.
//              : Dependency Injection(DI)
//               1) 생성자 주입
//                 - 협력 객체가 필수적인 경우,
//               2) 메소드 주입
//				   - 협력 객체가 필수적이지 않은 경우
//           => 의존성 주입 설계 문제점
//             : 보일러플레이트
//              F f;
//              A a(&f);
//              B b;
//              C c;
//				User user(&a, &b, &c);
//			=> 의존성 주입에 대한 보일러플레이트를 제거하기 위한 프레임워크를 사용하고 있습니다.
//			   C++: fruit
class IFileSystem {
public:
	virtual bool IsValid(const std::string& filename) = 0;
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	virtual ~FileSystem() {}

	bool IsValid(const std::string& filename) override {
		// ...
		// 현재의 파일 시스템에서 적합한 이름인지 체크합니다.
		return false;
	}
};

class Logger {
	IFileSystem* fs;
public:
	Logger(IFileSystem* p = nullptr) : fs(p) {
		// 기존의 사용방법 동일하게 만들어주는 것이 좋습니다.
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}
	// file.log
	//  => 확장자를 제외한 파일의 이름이 5글자 이상이어야 합니다.
	bool IsValidLogFilename(const std::string& filename) {
		//------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		if (name.size() < 5)
			return false;
		//------

		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
		// FileSystem fs;
		// return fs.IsValid(filename);
	}
};

//--------
#include <gtest/gtest.h>

// Logger logger
//  : logger ->FileSystem

// TestDoubleFileSystem fs;
// Logger logger(&fs);
//  : logger -> TestDoubleFileSystem
//   - Test Stub
class TestDoubleFileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};

// 파일의 확장자를 제외한 이름이 5글자 이상일 때 true를 반환하는지 검증한다.
TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue) {
	TestDoubleFileSystem fs;
	Logger logger(&fs);
	std::string validFilename = "valid_file.log";

	bool actual = logger.IsValidLogFilename(validFilename);

	EXPECT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}


// 파일의 확장자를 제외한 이름이 5글자 미만일 때 false를 반환하는지 검증한다.
TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	TestDoubleFileSystem fs;
	Logger logger(&fs);
	std::string invalidFilename = "bad.log";
	
	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}

//-----------
// Test Double - xUnit Test Pattern
//  : 이전에는 Mock(모의객체)라고 불렀습니다.
//
// 5가지 종류
// 1. Dummy
// 2. Stub
// 3. Fake
// 4. Spy
// 5. Mock
