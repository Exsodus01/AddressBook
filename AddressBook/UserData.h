#pragma once
#include "DataNode.h"
#include <string>

class UserData : public DataNode
{
	friend class UserList;

public:
	UserData();
	UserData(std::string Name, std::string Phone);
	~UserData();


	const std::string GetN();
	const std::string GetP();
	

	static int GetUserDataCount();

private:
	virtual std::string Getkey();
	virtual void PrintNode();


protected:
	std::string UserName;
	std::string UserPhone;

	static int UserDataCount;
};

