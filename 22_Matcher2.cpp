// Matcher 유래
//  => Hamcrest Matcher
//  => Assertion의 구문을 가독성있게 표현할 수 있도록 해준다.
//   "비교 표현의 확장 라이브러리"

// Google Mock은 Hamcrest Style의 단언문을 제공합니다.
#include <gmock/gmock.h>

int GetAge() { return 420; }
const char* GetMessage() { return "xHello"; }
const char* GetPattern() { return "Line"; }

using testing::Eq;
using testing::Lt;
using testing::StartsWith;
using testing::MatchesRegex;

TEST(HamcrestTest, Sample) {
	EXPECT_EQ(GetAge(), 42) << "GetAge 하였을 때";

	EXPECT_THAT(GetAge(), Eq(42)) << "GetAge 하였을 때";
	EXPECT_THAT(GetMessage(), StartsWith("Hello"));
	EXPECT_THAT(GetPattern(), MatchesRegex("Xine"));
}

class User {
public:
	User(const std::string& n, int a) : name(n), age(a) {}

// Property
	std::string GetName() const { return name; }
	int GetAge() const { return age; }
//

	FRIEND_TEST(UserTest, Sample2);
private:
// Field
	std::string name;
	int age;
};

// Property - Getter 
using testing::Property;
using testing::Field;

static std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User{..}";
}

TEST(UserTest, Sample2) {
	User user("Bom", 42);

	EXPECT_EQ(user.GetName(), "Tom");
	EXPECT_THAT(user, Property(&User::GetName, Eq("Tom")));

	EXPECT_THAT(user, Field(&User::age, Lt(10)));
}
