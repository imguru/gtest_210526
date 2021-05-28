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
#include <gmock/gmock.h>
#include <map>

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));

	FakeDatabase() {
		ON_CALL(*this, SaveUser).WillByDefault([this](const std::string& name, User* user) {
			SaveUserImpl(name, user);
		});

		ON_CALL(*this, LoadUser).WillByDefault([this](const std::string& name) {
			return LoadUserImpl(name);
		});
	}
	
private:
	void SaveUserImpl(const std::string& name, User* user) {
		data[name] = user;
	}

	User* LoadUserImpl(const std::string& name) {
		return data[name];
	}
};

static bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}

static std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User{name=" << user.GetName() << ", age=" << user.GetAge() << "}";
}

using testing::NiceMock;

TEST(UserManagerTest, Load) {
	// NiceMock<FakeDatabase> database;
	FakeDatabase database;
	UserManager manager(&database);  // !!!
	std::string name = "test_name";
	int age = 42;
	User expected = User(name, age);

	EXPECT_CALL(database, SaveUser(name, &expected));
	EXPECT_CALL(database, LoadUser(name));

	manager.Save(&expected);
	User* actual = manager.Load(name);

	// ASSERT_NE(actual, nullptr);
	// EXPECT_EQ(*actual, expected) << "Database에서 로드하였을 때";
}

















