
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

class Image {
public:
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}

	void Draw() {
		printf("Draw image...\n");
	}
};

int Image::allocCount = 0;

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
		allocCount = Image::allocCount;
	}

	void TearDown() override {
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
	}
};


TEST_F(ImageTest, Draw) {
	Draw();
}



















