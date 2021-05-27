
#include <gtest/gtest.h>

// 객체의 메모리 누수를 판단하는 목적으로 테스트를 이용할 수 있습니다.
//  1) 제품 코드(SUT)에 미리 정의되어야 하는 코드가 있습니다.
//     new / delete 연산자 재정의가 필요합니다.
//      - new Image
//       1. 메모리 할당                                 - operator new
//       2. 할당된 메모리를 대상으로 생성자 함수 호출
//
//      - delete p;
//       1. 소멸자 함수 호출
//       2. 메모리 해지                                 - operator delete
//  2) 테스트 코드에서만 이용해야 합니다.
//      - 조건부 컴파일 
//      g++ 7_비기능테스트2.cpp -lgtest -L. -I. -pthread -DGTEST_LEAK_TEST

#if 0
class Image {
public:
#ifdef GTEST_LEAK_TEST
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
#endif

	void Draw() {
		printf("Draw image...\n");
	}
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif
#endif

#ifdef GTEST_LEAK_TEST
#define DECLARE_GTEST_LEAK_TEST()			\
public:										\
	static int allocCount;					\
	void* operator new(size_t size) {		\
		++allocCount;						\
		return malloc(size);				\
	}										\
	void operator delete(void* p, size_t) {	\
		--allocCount;						\
		free(p);							\
	}

#define IMPLEMENT_GTEST_LEAK_TEST(classname)	\
	int classname::allocCount = 0
#else
#define DECLARE_GTEST_LEAK_TEST()
#define IMPLEMENT_GTEST_LEAK_TEST(classname)
#endif

class Image {
	DECLARE_GTEST_LEAK_TEST()
public:
	void Draw() {
		printf("Draw image...\n");
	}
};

IMPLEMENT_GTEST_LEAK_TEST(Image);

void Draw() {
	Image* image = new Image;
	image->Draw();

	// delete image;
}

//---------
class ImageTest : public testing::Test {
protected:
	int allocCount;
	void SetUp() override {
#ifdef GTEST_LEAK_TEST
		allocCount = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
#endif
	}
};


TEST_F(ImageTest, Draw) {
	Draw();
}



















