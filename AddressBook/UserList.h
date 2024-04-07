#pragma once
#include "DataNode.h"
#include <vector>

class UserList
{
public:
	UserList(DataNode* pHead);
	~UserList();


	std::vector<DataNode*> FindNode(const std::string key);
	int AddNewNode(DataNode* NewNode);

	void PrintAll();

	int RemoveNode(const std::string key);

	void Clear();

	void LoadFile();


protected:
	void RemoveList();
	void parseData(const char* data);
	DataNode* Head;




};

