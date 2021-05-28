
#include <gmock/gmock.h>
// #include <gtest/gtest.h>

class MP3 {
public:
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;
};

//------
// MOCK_METHOD(반환타입, 이름, (인자1, 인자2), (한정자1, 한정자2));

// 한정자
// 1. override: virtual 함수 - Optional

class MockMP3 : public MP3 {
public:
	// void Play() override {}
	MOCK_METHOD(void, Play, (), (override));
	// void Stop(int n) override {}
	MOCK_METHOD(void, Stop, (int n), (override));
};

TEST(MP3Test, Sample) {
	MockMP3 mock;         // !!!
}
