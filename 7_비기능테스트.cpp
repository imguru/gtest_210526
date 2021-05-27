// 7_비기능테스트.cpp
//   정의: 기능적인 부분 뿐 아니라 성능이나 메모리 등의 비기능적인 부분을 검증한다.

#include <string>
#include <unistd.h>

void OpenFile(const std::string& filename) {
	sleep(2);
}

//-----
#include <gtest/gtest.h>


#if 0
// OpenFile이 1초 안에 수행되는지 검증하고 싶다.
//  방법 1. TestSuite
class SampleTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(nullptr);
	}

	void TearDown() override {
		time_t duration = time(nullptr) - startTime;
		// printf("%ld\n", duration);
		EXPECT_LE(duration, 1) << "시간 초과: " << duration << " 초 걸림";
	}
};

TEST_F(SampleTest, OpenFile) {
	OpenFile("a.txt");
}
#endif
//  방법 2. 사용자 정의 단언문을 제공합니다.
//   => 매크로를 만들어봅니다.
#define EXPECT_TIMEOUT(fn, sec)                           					  \
		do {     															  \
		time_t startTime = time(nullptr);					 				  \
		fn;													  				  \
		time_t duration = time(nullptr) - startTime;          				  \
		EXPECT_LE(duration, sec) << "시간 초과: " << duration << " 초 걸림";  \
		} while (0)

TEST(SampleTest, OpenFile) {
	EXPECT_TIMEOUT(OpenFile("a.txt"), 1);
}

#if 0
TEST(SampleTest, OpenFile) {
	time_t startTime = time(nullptr);
	OpenFile("a.txt");
	time_t duration = time(nullptr) - startTime;
	EXPECT_LE(duration, 1) << "시간 초과: " << duration << " 초 걸림";
}
#endif









#if 0
TEST(SampleTest, OpenFile) {
	OpenFile("a.txt");
}
#endif
