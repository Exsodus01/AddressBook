#include "UserData.h"
#include <iostream>
int UserData::UserDataCount = 0;

UserData::UserData()
	:UserName(""), UserPhone("")
{
	
}

UserData::UserData(std::string Name, std::string Phone)
{
	UserName = Name;
	UserPhone = Phone;
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



int UserData::GetUserDataCount()
{
	return UserDataCount;
}

std::string UserData::Getkey()
{
	return UserName;
}

void UserData::PrintNode()
{
	std::cout << UserName << " " << UserPhone << std::endl;
}
