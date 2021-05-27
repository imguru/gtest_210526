// 12_테스트대역.cpp
#include <string>

class FileSystem {
public:
	virtual ~FileSystem() {}

	virtual bool IsValid(const std::string& filename) {
		// ...
		// 현재의 파일 시스템에서 적합한 이름인지 체크합니다.
		return true;
	}
};

class Logger {
public:
	// file.log
	//  => 확장자를 제외한 파일의 이름이 5글자 이상이어야 합니다.
	bool IsValidLogFilename(const std::string& filename) {
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		if (name.size() < 5)
			return false;

		FileSystem fs;
		return fs.IsValid(filename);
	}
};

//--------
#include <gtest/gtest.h>
// 파일의 확장자를 제외한 이름이 5글자 이상일 때 true를 반환하는지 검증한다.
TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid_file.log";

	bool actual = logger.IsValidLogFilename(validFilename);

	EXPECT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}


// 파일의 확장자를 제외한 이름이 5글자 미만일 때 false를 반환하는지 검증한다.
TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string invalidFilename = "bad.log";
	
	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}















