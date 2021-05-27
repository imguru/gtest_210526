
#include <iostream>

class IConnection {
public:
	virtual ~IConnection() {}
	
	virtual void Move(int x, int y) = 0;
};

class TCPConnection : public IConnection {
public:
	void Move(int x, int y) override {
		// 패킷을 만드어서 서버로 전송한다.
	}
};

class NetworkException : public std::exception {
public:
	const char* what() {
		return "Bad network start...";
	}
};

class Player {
	IConnection* conn;
public:
	Player(IConnection* p) : conn(p) {}

	void Move(int x, int y) {
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			printf("Network 오류 처리 로직..\n");
			throw e;
		}
	}
};
//-------------------
#include <gtest/gtest.h>

// Test Stub Pattern
//  의도: '다른 컴퓨넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 한다.
//   => 특수한 상황을 시뮬레이션 하고 싶다.
//    : 예외, 반환값, 시간 등의 제어가 불가능한 환경을 제어하는 목적으로 사용할 수 있습니다.

// 테스트 대역을 만드는 방법.
//  - 협력 객체의 인터페이스를 구현하는 형태로 만듭니다.
//    : 협력 객체의 인터페이스가 간결할수록 테스트 대역을 만들기 쉽습니다.

class StubConnection : public IConnection {
public:
	void Move(int x, int y) override {
		throw NetworkException();
	}
};

// Player의 Move가 Connection에서 예외가 발생했을 때, 
// NetworkException 외부 전파를 검증하고 싶다.
TEST(PlayerTest, Move) {
	// TCPConnection conn;
	StubConnection conn;  // 제품 코드를 사용하는 방식 그대로 테스트 코드를 작성할 수 있습니다.
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}




















