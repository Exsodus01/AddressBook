#include "UserData.h"

int UserData::UserDataCount = 0;

UserData::UserData()
	:UserName(""), UserPhone(""), Next(nullptr)
{
	
}

const std::string UserData::GetN()
{
	return UserName;
}

UserData::~UserData()
{
}

const std::string UserData::GetP()
{
	return UserPhone;
}

const UserData* UserData::GetNext()
{
	return Next;
}

int UserData::GetUserDataCount()
{
	return UserDataCount;
}
