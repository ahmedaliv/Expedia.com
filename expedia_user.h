#ifndef EXPEDIA_USER_H_INCLUDED
#define EXPEDIA_USER_H_INCLUDED


#include <bits/stdc++.h>
using namespace std;

enum class UserType {
	CusomterUser = 0, AdminUser = 1
};

class User {
protected:
	string user_name;
	string password;
	string name;
	string email;
	UserType type = UserType::CusomterUser;

public:
	User(const User&) = delete;
	void operator=(const User&) = delete;

	User() {
	}

	virtual ~User() {	// To allow dynamic casting, we need 1+ virtual function
	}

	string ToString() const ;


	void Read(const string &user_name);

	const string& GetEmail() const;
	void SetEmail(const string& email) ;
	const string& GetName() const;

	void SetName(const string& name);
	const string& GetPassword() const;
	void SetPassword(const string& password);
	const string& GetUserName() const;
	void SetUserName(const string& userName);

	UserType GetType() const ;

	void SetType(UserType type);
};

//////////////////////////////
// Admin User //




class Admin: public User {
protected:
public:
	Admin(const Admin&) = delete;
	void operator=(const Admin&) = delete;
	Admin() {
		SetType(UserType::AdminUser);
	}
};

#endif // EXPEDIA_USER_H_INCLUDED
