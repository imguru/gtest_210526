#include <stdio.h>

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual void Start() {
		printf("Start Engine...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p): engine(p) {}

	void Go() {
		// ...
		engine->Start();
		// ...
	}
};
//--------
#include <gmock/gmock.h>

class TestEngine : public Engine {
public:
	MOCK_METHOD(void, Start, (), (override));
};

// Car의 Go가 수행되었을 때, Engine의 Start가 제대로 호출되었는지 여불르 검증하고 싶다.
TEST(CarTest, Go) {
	TestEngine engine;
	Car car(&engine);

	EXPECT_CALL(engine, Start);

	car.Go();
}

#if 0
TEST(CarTest, Go) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// Engine 객체가 Start 되었는지 확인할 수 있는 기능이 제공되지 않아서,
	// 단언문을 작성할 수 없습니다.
}
#endif











