#include "UserList.h"
#include "UserData.h"
#include <iostream>

#include <Windows.h>
#include <vector>
#include <sstream>





UserList::UserList(DataNode* pHead)
	:Head(pHead)
{
}

UserList::~UserList()
{
	RemoveList();
	
}

 std::vector<DataNode*> UserList::FindNode(const std::string key)
{
	std::vector<DataNode*> result;
	DataNode* Tmp = Head;
	if (Tmp == nullptr) {
		return result;
	}

	while (Tmp!=nullptr) {
		if (Tmp->Getkey() == key) {
			result.push_back(Tmp);
			}
			Tmp = Tmp->GetNext();
	}
	if (result.empty()) {

		std::cout << "해당 이름이 존재하지 않습니다." << std::endl;
	}
	else
		for (auto n : result) {
			n->PrintNode();
		}
	return result;
}

int UserList::AddNewNode(DataNode* NewNode) //리스트가 빈 리스트가 아닌 이상 끝에 추가하는데 매번 끝까지 n회 탐색으로 찾아가야한다. Tail 포인터를 추가 고려
{
	if (Head == nullptr) {
		Head = NewNode;
		UserData::UserDataCount++;
		return UserData::UserDataCount;
	}

	DataNode* Search = Head;
	while (Search->Next != nullptr) {
		Search = Search->Next;
	}
	Search->Next = NewNode;
	UserData::UserDataCount++;

	return UserData::UserDataCount;
}

void UserList::PrintAll()
{
	if (Head == nullptr) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return;
	}

	DataNode* Tmp = Head;

	while (Tmp != nullptr) {
		Tmp->PrintNode();
		Tmp = Tmp->Next;
	}

}
int UserList::RemoveNode(const std::string Name)
{
	std::vector<DataNode*> DelList;
	DataNode* Ne; //vector에 요소를 추가할때 객체가 Next에 주소를 가지고 있어서 요소를 재삽입시 오류를 일으킴.
	DataNode* Tmp = Head;
	if (Tmp == nullptr) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return 0;
	}
	if (Head->Getkey() == Name) {
		Ne = Head->Next;
		Head->Next = nullptr;
		DelList.push_back(Head);
		Head = Ne;
	}


	while (Tmp->GetNext() != nullptr) {
		if (Tmp->Next->Getkey() == Name) {
			Ne = Tmp->Next->Next;
			Tmp->Next->Next = nullptr;
			DelList.push_back(Tmp->Next);
			Tmp->Next = Ne;
		}
		else {
			Tmp = Tmp->Next;
		}
	}
	
	
	int Num = 0;
	while (true) {
		if (DelList.size()) {
			int index = 1;
			for (auto n : DelList) {

				std::cout << index << ". ";
				index++;
				n->PrintNode();
			}
		}
		std::cout << '\n' << "위의 인덱스에서 지우고 싶은 인덱스 번호를 선택해주세요.(전체삭제는 -1, 그냥 나가기는 0)" << std::endl;
		
		std::cin >> Num;
		if (Num<-1 || Num>=DelList.size()) {
			std::cout << "잘못된 입력값입니다. 다시 입력하세요" << std::endl;
			continue;
		}



		if (Num == 0) {
			//삭제 예정 목록을 작성하고 아무것도 삭제하지 않는다면 다시 리스트에 추가해야한다.
			//Add함수 호출시 다시 카운트가 증가하므로 미리 추가할 만큼의 노드 숫자를 빼줘야한다.
			UserData::UserDataCount -= DelList.size();
			for (int i = 0; i < DelList.size(); i++) {
				AddNewNode(DelList[i]);
			}
			
			
			break;
		}
		else if (Num == -1) {
			UserData::UserDataCount -= DelList.size();
			for (int i = 0; i < DelList.size(); i++) {
				DataNode* del = DelList[i];
				delete del;
			}
			std::vector<DataNode*>().swap(DelList); //vector를 clear함과 동시에 메모리할당도 최소화, 여기서는 그냥 clear만 써도 지역변수로 사라질 벡터이다.

			break;
		}
		else {
			DataNode* del = DelList[Num - 1];
			delete del;
			DelList.erase(DelList.begin()+(Num-1));
			UserData::UserDataCount--;
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

	UnmapViewOfFile(srcText);
	CloseHandle(srcMap);
	CloseHandle(srcFile);
	
}


void UserList::RemoveList()
{
	if (Head == nullptr) {
		std::cout << "리스트가 존재하지 않습니다." << std::endl;
	}

	DataNode* Del;
	DataNode* Tmp = Head;
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
			AddNewNode(new UserData(name,phone)); // 추출한 이름과 전화번호로 새 노드 추가

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
		AddNewNode(new UserData(name,phone)); // 마지막 레코드에 대한 처리
	}
}
