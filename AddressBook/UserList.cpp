#include "UserList.h"
#include <iostream>

#include <Windows.h>

#include <sstream>



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

void UserList::LoadFile()
{
	//파일 열기
	HANDLE srcFile = CreateFile(
		L"Address_random.txt",
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
	if (srcFile == INVALID_HANDLE_VALUE) {
		std::cout << "파일 오픈에 실패했습니다. ERROR NUM :" << errno << std::endl;
		return;
	}
	//파일 사이즈 확인
	LARGE_INTEGER FileSize;
	DWORD UnitByte = 22;
	DWORD TmpSize;
	DWORD Total = 0;

	std::string Tmp(UnitByte,'\0');

	GetFileSizeEx(srcFile, &FileSize);
	std::cout << "파일의 사이즈 : " << FileSize.QuadPart << std::endl;

	while (true) {



		std::string Name, Phone;

		if (!ReadFile(srcFile, &Tmp[0], UnitByte, &TmpSize, nullptr)) {
			std::cout << "파일 읽기 실패" << std::endl;
			CloseHandle(srcFile);
			
			return;
		}
		
		std::string check=std::string(Tmp);
		std::istringstream iss(check);

		Total += TmpSize;

		iss >> Name >> Phone;

		

		AddNewNode(Name, Phone);
		if (Total == FileSize.QuadPart) {
			std::cout << "파일 처리가 끝났습니다." << std::endl;
			break;
		}

	}
	CloseHandle(srcFile);
	
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
