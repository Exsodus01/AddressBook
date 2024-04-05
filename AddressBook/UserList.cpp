#include "UserList.h"
#include <iostream>
UserList::UserList()
	:Head(nullptr)
{
	
	
}

UserList::~UserList()
{
	RemoveList();
	
}

UserData* UserList::FindNode(const std::string Name)
{
	UserData* Tmp = Head;

	while (Tmp!=nullptr) {
		if (Tmp->UserName == Name) {
			std::cout << Tmp->UserName << " " << Tmp->UserPhone << std::endl;
			return Tmp;
		}
		else
			Tmp = Tmp->Next;
	}
	std::cout << "해당 이름이 존재하지 않습니다." << std::endl;
	return nullptr;
}

int UserList::AddNewNode(const std::string Name, const std::string Phone)
{
	if (Head == nullptr) {
		Head = new UserData;
		Head->UserName = Name;
		Head->UserPhone = Phone;
		UserData::UserDataCount++;
		return UserData::UserDataCount;
	}


	


	UserData* Tmp = new UserData;
	Tmp->UserName = Name;
	Tmp->UserPhone = Phone;
	

	UserData* Search = Head;
	while (Search->Next != nullptr) {
		Search = Search->Next;
	}
	Search->Next = Tmp;
	UserData::UserDataCount++;

	return UserData::UserDataCount;
}

void UserList::PrintAll()
{
	if (Head == nullptr) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return;
	}

	UserData* Tmp = Head;

	while (Tmp != nullptr) {
		std::cout << Tmp->UserName << " " << Tmp->UserPhone << std::endl;
		Tmp = Tmp->Next;
	}

}

int UserList::RemoveNode(const std::string Name)
{
	UserData* Tmp = Head;
	UserData* Del;
	if (Head->UserName == Name) {
		Head = Head->Next;
		delete Tmp;
		UserData::UserDataCount--;
	}
	else {
		while (Tmp->Next != nullptr) {
			if (Tmp->Next->UserName == Name) {
				Del = Tmp->Next;
				Tmp->Next = Tmp->Next->Next;
				delete Del;
				UserData::UserDataCount--;
			}
			else
				Tmp = Tmp->Next;
		}
	}
	



	
	return UserData::UserDataCount;
}

void UserList::Clear()
{
	RemoveList();
}

void UserList::RemoveList()
{
	if (Head == nullptr) {
		std::cout << "리스트가 존재하지 않습니다." << std::endl;
	}

	UserData* Del;
	UserData* Tmp = Head;
	while (Tmp != nullptr) {
		if (Tmp->Next == nullptr) {
			Del = Tmp;
			delete Del;
			
			break;
		}
		
		
		
		Del = Tmp;
		Tmp = Tmp->Next;
		delete Del;
		
	}
	Head = nullptr;
	UserData::UserDataCount = 0;
	std::cout << "삭제 완료" << std::endl;


}
