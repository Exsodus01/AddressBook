#pragma once
#include <string>

class UserData
{
	friend class UserList;

public:
	UserData();
	~UserData();


	const std::string GetN();
	const std::string GetP();
	const UserData* GetNext();

	static int GetUserDataCount();

protected:
	std::string UserName;
	std::string UserPhone;


	UserData* Next;

	static int UserDataCount;
};

