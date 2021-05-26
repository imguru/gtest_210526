#include <gtest/gtest.h>
#include <string>

// xUnit Test Framework
// 1. Fixture
// 2. Assertions

struct User {
	int age;

	User(): age(42) {}

	int GetAge() const { return age; }
};

int foo() { return 42; }
int goo() { return 42; }
// User* hoo() { return nullptr; }
User* hoo() { return new User(); }

// 1. EXPECT_
// ASSERT_EQ / NE / LT / GT / LE / GE / TRUE / FALSE ...
// => 단언문이 실패할 경우 이후의 코드를 수행하지 않습니다.
// => 하나의 테스트 함수 안에서, 여러개의 단언문을 사용하는 좋지 않다.
//  한계: 하나의 기능에 대해서 중복된 테스트케이스가 만들어질 수 있습니다.

// EXPECT_EQ / NE / LT / GT / LE / GE / TRUE / FALSE ...
// => 단언문이 실패할 경우, 테스트의 결과는 실패가 되지만 이후의 코드는 수행됩니다.
//  : 죽은 단언문 / 중복된 테스트케이스
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual1 = foo();
	int actual2 = goo();
	User* user = hoo();

	ASSERT_NE(user, nullptr);
	EXPECT_EQ(expected, user->GetAge()) << "Reason User";
	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
	// ASSERT_EQ(expected, actual1) << "Reason 1";
	// ASSERT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
}

// 2. 문자열 단언문
//   std::string
//    - EXPECT_EQ / EXPECT_NE
//   const char* 
//    - EXPECT_STREQ/STRNE          : strcmp
//    - EXPECT_STRCASEQ/STRCASENE   : stricmp(MS) / strcasecmp(POSIX)
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";
	const char* s3 = s1.c_str();
	const char* s4 = "HEllo";

	EXPECT_EQ(s1, s2);
	// EXPECT_STREQ(s3, s4);
	EXPECT_STRCASEEQ(s3, s4);
}









