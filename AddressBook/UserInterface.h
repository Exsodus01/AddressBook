#pragma once
#include <boost/asio.hpp>


class UserList;
class UserInterface
{
public:
	UserInterface(UserList& rList);
	~UserInterface();


	void Add();

	void Search();

	void RemoveN();

	int PrintUI();

	int Run();

	void PrintList();

	void RemoveL();

	void LoadF();

	void ModeChange();

	void Multithread(int function_Num,boost::asio::io_service& io);

protected:
	UserList& List;

};

