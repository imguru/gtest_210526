
// main.cpp

// 1. GoogleTest의 헤더파일은 한개만 필요합니다.
#include <gtest/gtest.h>

// 테스트케이스를 만드는 방법
// - TEST(TestSuiteName, TestCaseName)

// SampleTest.Foo
TEST(SampleTest, Foo) {

}

TEST(SampleTest, Goo) {

}

// 아래의 코드는 거의 항상 동일합니다.
// - libgtest.a 에 main을 포함해서 사용하면 편리합니다.
// 2. main
#if 0
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif

// 라이브러리
// 1. 정적 라이브러리: libgtest.a  => 권장
//  - 라이브러리의 모든 바이너리가 실행 파일에 포함됩니다.
//  - 라이브러리의 코드가 변경되면, 실행 파일을 다시 빌드해야 합니다.
//  - 실행 파일 외의 별도의 라이브러리가 필요하지 않습니다.
//  - 배포가 편리합니다.

// 2. 동적 라이브러리: libgtest.so
// - 라이브러리의 바이너리가 실행 파일에 포함되지 않습니다.
// - 라이브러리 코드가 변경되어도, 실행 파일을 다시 빌드할 필요가 없습니다.
