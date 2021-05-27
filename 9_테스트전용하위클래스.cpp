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
#include <gtest/gtest.h>

// 테스트 전용 하위 클래스 패턴(Test Specific Subclass Pattern)
//  의도: SUT의 클래스가 테스트를 위한 기능을 제공하고 있지 않다면,
//        테스트 코드 안에서 자식 클래스를 통해 해당 기능을 제공하면 됩니다.
//        C++ 전제
//         - virtual 함수
class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine(): isStart(false) {}

	void Start() override {
		isStart = true;
	}

	bool IsStart() const {
		return isStart;
	}
};

TEST(CarTest, Go) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	EXPECT_TRUE(engine.IsStart()) << "Car가 Go했을 때";
}
#if 0
// Car의 Go가 수행되었을 때, Engine의 Start가 제대로 호출되었는지 여불르 검증하고 싶다.
TEST(CarTest, Go) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// Engine 객체가 Start 되었는지 확인할 수 있는 기능이 제공되지 않아서,
	// 단언문을 작성할 수 없습니다.
}
#endif











