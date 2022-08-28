#include "expedia_user.h"

string User::ToString() const {
		ostringstream oss;
		oss << "Name: " << user_name;
		if (type == UserType::AdminUser)
			oss << " | Admin";
		oss << "\n";
		oss << "Email: " << email << "\n";
		oss << "User name: " << user_name << "\n";
		return oss.str();
	}

void User::Read(const string &user_name) {
		SetUserName(user_name);

		string str;

		cout << "Enter password: ";
		cin >> str;
		SetPassword(str);

		cout << "Enter name: ";
		cin >> str;
		SetName(str);

		cout << "Enter email: ";
		cin >> str;
		SetEmail(str);
	}

	const string& User::GetEmail() const {
		return email;
	}

	void User::SetEmail(const string& email) {
		this->email = email;
	}

	const string& User::GetName() const {
		return name;
	}

	void User::SetName(const string& name) {
		this->name = name;
	}

	const string& User::GetPassword() const {
		return password;
	}

	void User::SetPassword(const string& password) {
		this->password = password;
	}

	const string& User::GetUserName() const {
		return user_name;
	}

	void User::SetUserName(const string& userName) {
		user_name = userName;
	}

	UserType User::GetType() const {
		return type;
	}

	void User::SetType(UserType type) {
		this->type = type;
	}


