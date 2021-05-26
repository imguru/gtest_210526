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

// 3. 부동 소수점
//   - EXPECT_DOUBLE_EQ / EXPECT_FLOAT_EQ
//   - EXPECT_NEAR 
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	EXPECT_DOUBLE_EQ(a, b); // 4ULP: https://en.wikipedia.org/wiki/Unit_in_the_last_place
	EXPECT_NEAR(a, b, 0.000000001);
}

// 4. 예외 테스트
void IsValidFilename(const std::string& filename) {
	if (filename.empty()) {
		throw std::invalid_argument("filename should not empty");	
		// throw 1;
	}

	// ....
}

// IsValidFilename에 빈문자열을 전달할 경우, invalid_argument 예외가 발생하는지 여부를 검증한다.
//  - EXPECT_THROW
//    EXPECT_ANY_THROW
TEST(GoogleTest, Sample4) {
	std::string emptyFilename = "";

	EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument);
	EXPECT_ANY_THROW(IsValidFilename(emptyFilename));
}

#if 0
TEST(GoogleTest, Sample4) {
	std::string emptyFilename = "";

	try {
		IsValidFilename(emptyFilename);
		FAIL() << "기대한 예외가 발생되지 않았음";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였음";
	}
}
#endif

// JUnit4 - @Ignore
// JUnit5 - @Disabled

// 5. 테스트 비활성화
//  - 테스트를 비활성화하기 위해서 주석처리하면,'잊혀진 테스트'가 될 가능성이 높습니다.
//   : 테스트의 결과에 포함되지 않지만, 유지보수의 대상의 
//     테스트가 존재한다는 사실을 지속적으로 알려줄 수 있어야 한다.
//     => TestSuite 이름 또는 TestCase 이름이 DISABLED_ 로 시작하면 비활성화됩니다.
//     => 비활성화된 테스트도 명령행 인자를 통해서 수행할 수 있습니다.
//     : ./a.out --gtest_also_run_disabled_tests
TEST(GoogleTest, DISABLED_Sample5) {
	FAIL() << "아직 작성 중입니다.";
}

class DISABLED_SampleTest : public testing::Test {};
TEST_F(DISABLED_SampleTest, Test1) {
}
TEST_F(DISABLED_SampleTest, Test2) {
}

// 6. 테스트 필터 기능을 제공합니다.
class CalcTest : public testing::Test {};
// CalcTest.Add
TEST_F(CalcTest, Add) {}
// CalcTest.Sub
TEST_F(CalcTest, Sub) {}

class TerminalTest : public testing::Test {};
TEST_F(TerminalTest, Connect) {}
TEST_F(TerminalTest, Disconnec) {}






























