// 12_테스트대역2.cpp
#include <string>

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
#include <gmock/gmock.h>

class TestDoubleFileSystem : public IFileSystem {
public:
	MOCK_METHOD(bool, IsValid, (const std::string& filename), (override));
};
using testing::Return;
using testing::NiceMock;

TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue) {
	NiceMock<TestDoubleFileSystem> fs;
	ON_CALL(fs, IsValid).WillByDefault(Return(true));
	Logger logger(&fs);
	std::string validFilename = "valid_file.log";

	bool actual = logger.IsValidLogFilename(validFilename);

	EXPECT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	NiceMock<TestDoubleFileSystem> fs;
	ON_CALL(fs, IsValid).WillByDefault(Return(true));
	Logger logger(&fs);
	std::string invalidFilename = "bad.log";
	
	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}
