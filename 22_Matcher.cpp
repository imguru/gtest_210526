
class Printer {
public:
	virtual ~Printer() {}

	virtual void Print(int n) = 0;
	virtual void Print(char c) = 0;
};

void Print(Printer* p) {
	p->Print(42);        // Print(int)
	p->Print('A');       // Print(char)
}

#include <gmock/gmock.h>

class MockPrinter : public Printer {
public:
	MOCK_METHOD(void, Print, (int n), (override));
	MOCK_METHOD(void, Print, (char c), (override));
};


using testing::TypedEq;
using testing::Matcher;
using testing::An;
TEST(PrinterTest, Print) {
	MockPrinter mock;

	// 1) TypedEq
	// EXPECT_CALL(mock, Print(TypedEq<int>(42)));
	// EXPECT_CALL(mock, Print(TypedEq<char>('A')));
	
	// 2) Matcher<T>
	// Matcher<int> arg1 = Matcher<int>(42);
	// Matcher<char> arg2 = Matcher<char>('A');
	// EXPECT_CALL(mock, Print(arg1));
	// EXPECT_CALL(mock, Print(arg2));
	
	// 3) An<T>
	EXPECT_CALL(mock, Print(An<int>()));
	EXPECT_CALL(mock, Print(An<char>()));

	Print(&mock);
}

// 오버로딩
// 1. 정확한 타입
// 2. 프로모션
//   char ->int
// 3. 타입 변환(하위 타입)
//   int -> char
// 4. 가변 인자

// void foo(...) { printf("foo(...)\n"); }
// void foo(int n) { printf("foo(int)\n"); }
// void foo(char c) { printf("foo(char)\n"); }
#if 0
int main() {
	foo(42);
	foo('A');
}
#endif
