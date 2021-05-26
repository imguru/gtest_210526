#include <string>

#include <unistd.h> // sleep
class Terminal {
public:
	// 만약 Connect() / Disconnect()가 느립니다.
	void Connect() { sleep(2); }
	void Disconnect() { sleep(1); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}
	
	bool IsLogin() { return true; }
};

//-----------
#include <gtest/gtest.h>

class TerminalTest : public testing::Test {
protected:
	static Terminal* term;
	
	TerminalTest() {
		printf("TerminalTest()\n");
	}

	~TerminalTest() {
		printf("~TerminalTest()\n");
	}

	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
		term = new Terminal;
		term->Connect();
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
		term->Disconnect();
		delete term;
	}

	void SetUp() override {
		printf("SetUp()\n");
		// term = new Terminal;
		// term->Connect();
	}

	void TearDown() override {
		printf("TearDown()\n");
		// term->Disconnect();
		// delete term;
	}
};

// static
Terminal* TerminalTest::term = nullptr;


// SetUp() / TearDown()                 - Per Testcase
// SetUpTestSuite / TearDownTestSuite   - Per TestSuite
#if 0
//---- SetUpTestSuite / SetUpTestCase  // static
TerminalTest* ts = new TerminalTest;
ts->SetUp();
ts->LoginTest();
ts->TearDown();
delete ts;

TerminalTest* ts = new TerminalTest;
ts->SetUp();
ts->LogoutTest();
ts->TearDown();
delete ts;
//---- TearDownTestSuite / TearDownTestCase // static
#endif

// 가정: 만약 픽스쳐 설치와 해체에서 호출되는 함수가 느려서,
//       "느린 테스트 문제"가 발생하였습니다.
// 해결방법: 스위트 픽스쳐
//      => "신선한 픽스쳐 전략" => "공유 픽스쳐 전략"
//        공유 픽스쳐 전략: 더 빠르게 동작하지만, 테스트 스위트내의 모든 테스트케이스가
//                          픽스쳐를 공유합니다.
//                          공유하는 픽스쳐가 망가질 경우, 테스트의 결과를 신뢰할 수 없는
//                          "변덕스러운 테스트" 문제가 발생할 수 있습니다.
//                           : 공유 픽스쳐의 상태에 따라 테스트의 결과가 변할 수 있다.

// Slow Test
//  1) 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//  2) 테스트가 너무 느려서, 아무도 코드가 변경되어도 테스트를 수행하지 않는다.


TEST_F(TerminalTest, Login) {
	term->Login("test_id", "test_password");

	ASSERT_TRUE(term->IsLogin()) << "로그인하였을 때";
}

TEST_F(TerminalTest, Logout) {
	term->Login("test_id", "test_password");
	term->Logout();

	ASSERT_FALSE(term->IsLogin()) << "로그아웃하였을 때";
}

TEST_F(TerminalTest, Foo) {}
TEST_F(TerminalTest, Goo) {}

#if 0
TEST(TerminalTest, Login) {
	Terminal* term = new Terminal;
	term->Connect();

	term->Login("test_id", "test_password");

	ASSERT_TRUE(term->IsLogin()) << "로그인하였을 때";

	term->Disconnect();
	delete term;
}

TEST(TerminalTest, Logout) {
	Terminal* term = new Terminal;
	term->Connect();

	term->Login("test_id", "test_password");
	term->Logout();

	ASSERT_FALSE(term->IsLogin()) << "로그아웃하였을 때";

	term->Disconnect();
	delete term;
}
#endif
