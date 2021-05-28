
#include <gmock/gmock.h>

// 1. Interface
// 2. Class
// 3. Template Class

template <typename T>
class StackInterface {
public:
	virtual ~StackInterface() {}

	virtual int GetSize() const = 0;
	virtual void Push(const T& x) = 0;
};

// Template Mocking
template <typename T>
class MockStack : public StackInterface<T> {
public:
	MOCK_METHOD(int, GetSize, (), (const, override));
	MOCK_METHOD(void, Push, (const T& x), (override));
};

//------
template <typename T>
void UseStack(StackInterface<T>* p) {
	// p->GetSize();
	// p->Push(T());
}

TEST(StackTest, UseStack) {
	MockStack<int> mock;

	EXPECT_CALL(mock, GetSize);
	EXPECT_CALL(mock, Push);

	UseStack(&mock);
}












