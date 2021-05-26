
// 전역 픽스쳐(Global Fixture)
//  => xUnit Test Framework의 기능이 아닌, 
//     GoogleTest 고유의 기능입니다.
//
//  Global Fixture     - Google Test / 프로그램 시작 끝에 수행되는 SetUp / TearDown을 정의합니다.
//  Test Suite Fixture - xUnit
//  Test Fixture       - xUnit

#include <gtest/gtest.h>

class TestEnvironment : public testing::Environment {
public:
	void SetUp() override {
		printf("TestEnvironment::SetUp()\n");
	}

	void TearDown() override {
		printf("TestEnvironment::TearDown()\n");
	}
};
// TestEnvironment를 Google Test Framework에 등록하는 방법
//   => main() 직접 정의 O / main() 직접 정의 X
//  1. main 안에서 수행 => main() 함수 직접 정의하는 것이 좋습니다.
//  2. 전역 변수를 통해 등록
//    => main 함수가 호출되기 이전에 전역 변수의 초기화가 수행된다.

// testing::Environment* env = testing::AddGlobalTestEnvironment(new TestEnvironment);
// 프레임워크에 등록하는 모든 객체는 new를 통해 생성되어야 합니다.

TEST(SampleTest, foo) {}
TEST(SampleTest, goo) {}
TEST(CalcTest, foo) {}
TEST(CalcTest, goo) {}

// libgtest.a에 gtest_main.o를 제거하고 사용해야 합니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	
	testing::AddGlobalTestEnvironment(new TestEnvironment);
	testing::AddGlobalTestEnvironment(new TestEnvironment);
	testing::AddGlobalTestEnvironment(new TestEnvironment);

	return RUN_ALL_TESTS();
}









