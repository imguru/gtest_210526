
#include <string>

// DAO(Database Access Object)
class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a): name(n), age(a) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

class IDatabase {
public:
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p): database(p) {}

	void Save(User* p) {
		database->SaveUser(p->GetName(), p);
	}

	User* Load(const std::string& name) {
		return database->LoadUser(name);
	}

	bool IsExist(const std::string& name) {
		return Load(name) != nullptr;
	}
};

//------------------
#include <gtest/gtest.h>
#include <map>

// 문제: 아직 데이터베이스 구현체가 존재하지 않습니다.
// Fake Object Pattern
//   의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트되지 않은 요구사항 있을 때
//   방법: 동일한 기능을 수행하는 가벼운 테스트 대역을 만들어서 테스트를 수행한다.
//       1) 의존 객체가 준비되지 않았을 때
//       2) 의존 객체가 너무 느려서 느린 테스트가 문제가 발생하였을 때
//       3) 의존 객체가 사용하기 어려울 때
class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		// return data[name];
		// return new User("Tom", 42);
		return nullptr;
	}
};

// EQ(==), NE(!=), LT(<), GT(>), LE(<=), GE(>=) ...
static bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}

static std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User{name=" << user.GetName() << ", age=" << user.GetAge() << "}";
}

TEST(UserManagerTest, Load) {
	FakeDatabase database;
	UserManager manager(&database);  // !!!
	std::string name = "test_name";
	int age = 42;
	User expected = User(name, age);

	manager.Save(&expected);
	User* actual = manager.Load(name);

	ASSERT_NE(actual, nullptr);
	EXPECT_EQ(*actual, expected) << "Database에서 로드하였을 때";
	// - 사용자 정의 객체를 대상으로 단언 매크로를 사용하기 위해서는
	//   연산에 해당하는 연산자 오버로딩 함수가 제공되어야 합니다.
}

















