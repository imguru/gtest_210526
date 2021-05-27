

bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0) 
			return false;
	}
	return true;
}

#include <gtest/gtest.h>

TEST(PrimeTest, IsPrime) {
	int data[] = { 2, 3, 5, 6, 7, 11, 13, 15, 17, 19, 23 };

	for (int i = 0 ; i < sizeof(data) / sizeof(data[0]); ++i) {
		EXPECT_TRUE(IsPrime(data[i])) << "data[i]: " << data[i];
	}
}

#if 0
// EXPECT_ : 죽은 단언문의 문제가 발생합니다.
//  => EXPECT_
//  => 코드 중복
TEST(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(6));
	EXPECT_TRUE(IsPrime(7));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(15));
	EXPECT_TRUE(IsPrime(17));
	EXPECT_TRUE(IsPrime(19));
	EXPECT_TRUE(IsPrime(23));
}
#endif
