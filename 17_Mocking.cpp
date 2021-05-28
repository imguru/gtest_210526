
#include <gmock/gmock.h>
// #include <gtest/gtest.h>

class MP3 {
public:
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;

	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;

	virtual std::pair<bool, int> GetPair() const = 0;
	virtual bool CheckMap(std::map<int, double> a, bool b) = 0;
};

//------
// MOCK_METHOD(반환타입, 이름, (인자1, 인자2), (한정자1, 한정자2));

// 한정자
// 1. override: virtual 함수 - Optional
// 2. const: Required
// 3. noexcept: Required

// Type Aliasing(Typedef)
using BoolIntPair = std::pair<bool, int>;
using IntDoubleMap = std::map<int, double>;

class MockMP3 : public MP3 {
public:
	// std::pair<bool, int> GetPair() const override {}
	//  - 템플릿 타입 인자가 2개 이상 존재할 경우, 괄호가 필요합니다.
	// MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));
	// MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (override));
	
	// - Type Alising
	MOCK_METHOD(BoolIntPair, GetPair, (), (const, override));
	MOCK_METHOD(bool, CheckMap, (IntDoubleMap a, bool b), (override));

	// std::string GetName() const override {}
	MOCK_METHOD(std::string, GetName, (), (const, override));
	// void Foo() noexcept override {}
	MOCK_METHOD(void, Foo, (), (noexcept, override));

	// void Play() override {}
	MOCK_METHOD(void, Play, (), (override));
	// void Stop(int n) override {}
	MOCK_METHOD(void, Stop, (int n), (override));
};

TEST(MP3Test, Sample) {
	MockMP3 mock;         // !!!
}
