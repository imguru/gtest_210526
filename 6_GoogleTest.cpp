#include <gtest/gtest.h>
#include <string>

// xUnit Test Framework
// 1. Fixture
// 2. Assertions

int foo() { return 420; }
int goo() { return 420; }

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
	
	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
	// ASSERT_EQ(expected, actual1) << "Reason 1";
	// ASSERT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
}
