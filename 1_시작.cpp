

#include <gtest/gtest.h>

// Test Coverage
//  - 정의: 테스트 코드에 의해서 수행된 제품 코드의 비율
//  - 테스트 커버리지 테스트 코드의 품질과 상관없다.

// xUnit(1.10) - TestSuite / TestCase
// 1.10 이전   - TestCase  / Test

// TestSuite
//  - TestSuite
//    - TestCase1
//    - TestCase2
//  - SampleTest
//    - Foo
//    - Goo
TEST(TestSuite, TestCase1) {
	// 명시적으로 테스트를 실패하는 방법
	//  - 테스트가 실패할 경우, 테스트의 실패 원인에 대한 설명이 필요합니다.
	FAIL();
}

TEST(TestSuite, TestCase2) {
	FAIL() << "아직 작성중입니다.";
}

TEST(SampleTest, Foo) {
	SUCCEED();
}

TEST(SampleTest, Goo) {

}
