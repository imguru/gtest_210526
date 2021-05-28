
#include <gmock/gmock.h>

// 행위 기반 검증(동작 검증)
// 1. 함수 호출 여부
// 2. 함수 호출 횟수 + 인자 검증
// 3. 함수 호출 순서

#include <vector>

class User {
public:
	virtual ~User() {}

	virtual void Go(int x, int y) = 0;
	virtual void Print(const std::vector<int>& numbers) = 0;
};

class MockUser : public User {
public:
	MOCK_METHOD(void, Go, (int x, int y), (override));
	MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (override));
};

void Sample1(User* p) {
	p->Go(10, 20);
	p->Go(20, 30);
}

// 1. 함수 호출 여부
//   : EXPECT_CALL
TEST(UserTest, Sample1) {
	MockUser mock;

	EXPECT_CALL(mock, Go(10, 20));
	EXPECT_CALL(mock, Go(20, 30));

	Sample1(&mock);
}

void Sample2(User* p) {
	p->Go(10, 121);
	p->Go(11, -42);
	p->Go(12, -53);
	p->Go(13, 114);
	p->Go(14, 0);
}

// 2. 함수 호출 횟수(인자 매칭(Matcher)에 따라서 판단되는 횟수가 달라집니다)
//   : EXPECT_CALL(..).Times(...)

using testing::_;   // 모든 것과 매칭
using testing::Gt;  // >
using testing::Eq;  // ==
using testing::Ne;  // !=
using testing::Lt;  // <
using testing::Ge;  // >=
using testing::Le;  // <=
using testing::AllOf; // &&
using testing::AnyOf; // ||
using testing::Not;   // !
using testing::Matcher;

TEST(UserTest, Sample2) {
	MockUser mock;

	// EXPECT_CALL(mock, Go).Times(4);
	// EXPECT_CALL(mock, Go(Eq(10), Gt(20))).Times(4);
	// EXPECT_CALL(mock, Go(Eq(10), _)).Times(4);
	
	// arg#1: arg1 >= 10 && arg1 < 20
	// arg#2: arg2 > 100 || arg2 <= 0
	Matcher<int> arg1 = AllOf(Ge(10), Lt(20));
	Matcher<int> arg2 = AnyOf(Gt(100), Le(0));
	EXPECT_CALL(mock, Go(arg1, arg2)).Times(5);

	Sample2(&mock);
}

void Sample3(User* p) {
	std::vector<int> v = { 10, 20, 30, 40, 50 };
	p->Print(v);
}

using testing::ElementsAreArray;
using testing::ElementsAre;
using testing::UnorderedElementsAreArray;
using testing::UnorderedElementsAre;

TEST(UserTest, Sample3) {
	MockUser mock;

	// EXPECT_CALL(mock, Print({10, 20, 30, 40, 50})); - Compile error!
	// Matcher<int> expected_args[] = { Gt(0), Le(25), Gt(20), Eq(40), Lt(90) };
	// EXPECT_CALL(mock, Print(ElementsAreArray(expected_args)));
	// EXPECT_CALL(mock, Print(ElementsAre(Gt(0), Le(25), Gt(20), Eq(40), Lt(90))));
	Matcher<int> expected_args[] = { Le(25), Gt(20), Lt(90), Gt(0), Eq(40) };
	EXPECT_CALL(mock, Print(UnorderedElementsAreArray(expected_args)));

	Sample3(&mock);
}

void Sample4(User* p) {
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(10, 20);
}

// Times
using testing::AtLeast;
using testing::AtMost;
using testing::Between;
using testing::AnyNumber;

TEST(UserTest, Sample4) {
	MockUser mock;

	// EXPECT_CALL(mock, Go).Times(AtLeast(1));
	// EXPECT_CALL(mock, Go).Times(AtMost(3));
	// EXPECT_CALL(mock, Go).Times(Between(1, 4));
	EXPECT_CALL(mock, Go).Times(AnyNumber());

	Sample4(&mock);
}

class Foo {
public:
	virtual ~Foo() {}

	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
	virtual void Forth() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
};

void Sample5(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}

// 3. 호출 순서
//  First -> Second -> Third ->Forth
//   : InSequence;
using testing::InSequence;
TEST(FooTest, Sample5) {
	MockFoo mock;
	InSequence seq; // !!!

	EXPECT_CALL(mock, First);
	EXPECT_CALL(mock, Second);
	EXPECT_CALL(mock, Third);
	EXPECT_CALL(mock, Forth);

	Sample5(&mock);
}

void Sample6(Foo* p) {
	p->First();
	p->Third();
	p->Second();
	p->Forth();
}
// First  -> Second         : seq1
//        |
//        |
//        -> Third -> Forth : seq2
// : Seqeunce

//  EXPECT_CALL(...).InSequence(seq1, ..)
using testing::Sequence;
TEST(FooTest, Sample6) {
	MockFoo mock;
	Sequence seq1, seq2;

	EXPECT_CALL(mock, First).InSequence(seq1, seq2);
	EXPECT_CALL(mock, Second).InSequence(seq1);
	EXPECT_CALL(mock, Third).InSequence(seq2);
	EXPECT_CALL(mock, Forth).InSequence(seq2);

	Sample6(&mock);
}

// Mock / InSequence / Sequence
//  => 파괴될 때 판단이 수행됩니다.
//  => 지역 객체로 관리하는게 편리합니다.





