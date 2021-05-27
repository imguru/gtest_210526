

#include <gtest/gtest.h>

// Test Suite
//  - SampleTest
//     - Foo
//     - Goo
//  - MyTest
//     - Foo
//     - Goo

TEST(SampleTest, Foo) { FAIL(); }
TEST(SampleTest, Goo) {}
TEST(MyTest, Foo) { FAIL(); }
TEST(MyTest, Goo) {}

// 모든 테스트 케이스가 수행될 때마다 추가적인 작업을 수행하고 싶습니다.
//  => Google Test Event Listener
#if 0
class MyTestListener : public testing::TestEventListener {
};
#endif

using testing::TestInfo;
using testing::TestSuite;
class MyTestListener : public testing::EmptyTestEventListener {
public:
	void OnTestSuiteStart(const TestSuite& test_suite) override {
		printf("Testsuite Start: %s\n", test_suite.name());
	}

	void OnTestSuiteEnd(const TestSuite& test_suite) override {
		printf("Testsuite End\n");
	}

	void OnTestStart(const TestInfo& test_info) override {
		printf("Testcase Start\n");
	}

	void OnTestEnd(const TestInfo& test_info) override {
		printf("Testcase End: %s\n",
			test_info.result()->Passed() ? "PASS" : "FAIL"
		);
	}
};

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	// 리스너 등록 방법
	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new MyTestListener);

	// Google Test Default Printer도 리스너 기반입니다.
	delete listeners.Release(listeners.default_result_printer());

	return RUN_ALL_TESTS();
}
