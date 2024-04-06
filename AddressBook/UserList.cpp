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
	//zero - copy를 위한 파일 매핑 객체
	LARGE_INTEGER FileSize;
	GetFileSizeEx(srcFile, &FileSize);
	HANDLE srcMap = CreateFileMapping(
		srcFile,
		nullptr, // 보안속성은 상속
		PAGE_READONLY,//읽기전용 매핑 객체
		0,				//상위 32비트
		FileSize.QuadPart,
		nullptr			//매핑 객체의 이름으로 다른 프로세스에서는 이 프로세스에 이름으로 접근하는데 이는 IPC의 공유메모리기법 때문.
	);


	//LPVOID 형태로 반환하는 함수라서 형변환 필요
	char* srcText = (char*)MapViewOfFile(
		srcMap,
		FILE_MAP_READ,
		0,				//상위32 시작
		0,				//하위32 시작
		0				//매핑할 데이터 크기 바이트 단위 지정 , 0이면 파일 전체
	);

	parseData(srcText);




	
	
	
	/* string에 한번 복사후 iss로 파싱해서 처리
	//파일 사이즈 확인
	
	DWORD UnitByte = 22;
	DWORD TmpSize;
	DWORD Total = 0;

	std::string Tmp(UnitByte,'\0');

	
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
	*/
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

void UserList::parseData(const char* data)
{
	std::string name, phone; // 이름과 전화번호를 저장할 변수
	const char* tokenStart = data; // 현재 토큰(필드)의 시작
	const char* p = data; // 데이터를 순회하는 포인터

	while (*p) { // 널 문자를 만날 때까지 반복
		if (*p == ' ') { // 필드 구분자를 만나면 (이름과 전화번호 사이)
			name.assign(tokenStart, p - tokenStart); // 이름 추출
			tokenStart = p + 1; // 토큰 시작을 다음 위치로 업데이트
		}
		else if (*p == '\n') { // 레코드 구분자를 만나면 (각 라인의 끝)
			phone.assign(tokenStart, p - tokenStart); // 전화번호 추출
			AddNewNode(name, phone); // 추출한 이름과 전화번호로 새 노드 추가

			// 다음 레코드 처리를 위해 변수 초기화
			name = "";
			phone = "";
			tokenStart = p + 1;
		}
		++p; // 포인터 이동
	}

	// 파일 끝에 도달했을 때 마지막 레코드 처리
	if (p != tokenStart) {
		phone.assign(tokenStart, p - tokenStart); // 마지막 전화번호 추출
		AddNewNode(name, phone); // 마지막 레코드에 대한 처리
	}
}
