#pragma once
#include "UserData.h"

class UserList
{
public:
	UserList();
	~UserList();


	UserData* FindNode(const std::string Name);
	int AddNewNode(const std::string Name, const std::string Phone);

	void PrintAll();

	int RemoveNode(const std::string Name);

	void Clear();

	void LoadFile();


protected:
	void RemoveList();
	void parseData(const char* data);
	UserData* Head;




};

