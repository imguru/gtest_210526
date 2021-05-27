#ifndef USER_H
#define USER_H

#include <gtest/gtest.h>

class User {
private:
	int age;
public:
	FRIEND_TEST(UserTest, NextYear);

	User(): age(42) {}

	void NextYear() {
		age += 1;
	}

// protected:
private:
	int GetAge() const {
		return age;
	}
};

#endif
