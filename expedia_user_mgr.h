#ifndef EXPEDIA_USER_MGR_H_INCLUDED
#define EXPEDIA_USER_MGR_H_INCLUDED

#include "expedia_user.h"
#include "expedia_payment_card.h"
#include "expedia_customer.h"
#include "helper_functions.h"
#include <iostream>
#include <map>
using std::map;
using std::string;


class UsersManager {
protected:
	User* current_user = nullptr;
	map<string, User*> userame_userobject_map;

	void FreeLoadedData() ;
public:

	UsersManager() ;
	~UsersManager() ;

	UsersManager(const UsersManager&) = delete;
	void operator=(const UsersManager&) = delete;

	void LoadDatabase();

	void AccessSystem() ;

	void DoLogin() ;

	void DoSignUp() ;

	User* GetCurrentUser() const;
};

#endif // EXPEDIA_USER_MGR_H_INCLUDED
