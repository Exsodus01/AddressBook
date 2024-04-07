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

		std::cout << "�ش� �̸��� �������� �ʽ��ϴ�." << std::endl;
	}
	else
		for (auto n : result) {
			n->PrintNode();
		}
	return result;
}

int UserList::AddNewNode(DataNode* NewNode) //����Ʈ�� �� ����Ʈ�� �ƴ� �̻� ���� �߰��ϴµ� �Ź� ������ nȸ Ž������ ã�ư����Ѵ�. Tail �����͸� �߰� ���
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
		std::cout << "����Ʈ�� ����ֽ��ϴ�." << std::endl;
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
	DataNode* Ne; //vector�� ��Ҹ� �߰��Ҷ� ��ü�� Next�� �ּҸ� ������ �־ ��Ҹ� ����Խ� ������ ����Ŵ.
	DataNode* Tmp = Head;
	if (Tmp == nullptr) {
		std::cout << "����Ʈ�� ����ֽ��ϴ�." << std::endl;
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
		std::cout << '\n' << "���� �ε������� ����� ���� �ε��� ��ȣ�� �������ּ���.(��ü������ -1, �׳� ������� 0)" << std::endl;
		
		std::cin >> Num;
		if (Num<-1 || Num>=DelList.size()) {
			std::cout << "�߸��� �Է°��Դϴ�. �ٽ� �Է��ϼ���" << std::endl;
			continue;
		}



		if (Num == 0) {
			//���� ���� ����� �ۼ��ϰ� �ƹ��͵� �������� �ʴ´ٸ� �ٽ� ����Ʈ�� �߰��ؾ��Ѵ�.
			//Add�Լ� ȣ��� �ٽ� ī��Ʈ�� �����ϹǷ� �̸� �߰��� ��ŭ�� ��� ���ڸ� ������Ѵ�.
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
			std::vector<DataNode*>().swap(DelList); //vector�� clear�԰� ���ÿ� �޸��Ҵ絵 �ּ�ȭ, ���⼭�� �׳� clear�� �ᵵ ���������� ����� �����̴�.

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
	//���� ����
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
		std::cout << "���� ���¿� �����߽��ϴ�. ERROR NUM :" << errno << std::endl;
		return;
	}
	//zero - copy�� ���� ���� ���� ��ü
	LARGE_INTEGER FileSize;
	GetFileSizeEx(srcFile, &FileSize);
	HANDLE srcMap = CreateFileMapping(
		srcFile,
		nullptr, // ���ȼӼ��� ���
		PAGE_READONLY,//�б����� ���� ��ü
		0,				//���� 32��Ʈ
		FileSize.QuadPart,
		nullptr			//���� ��ü�� �̸����� �ٸ� ���μ��������� �� ���μ����� �̸����� �����ϴµ� �̴� IPC�� �����޸𸮱�� ����.
	);


	//LPVOID ���·� ��ȯ�ϴ� �Լ��� ����ȯ �ʿ�
	char* srcText = (char*)MapViewOfFile(
		srcMap,
		FILE_MAP_READ,
		0,				//����32 ����
		0,				//����32 ����
		0				//������ ������ ũ�� ����Ʈ ���� ���� , 0�̸� ���� ��ü
	);

	parseData(srcText);




	
	
	
	/* string�� �ѹ� ������ iss�� �Ľ��ؼ� ó��
	//���� ������ Ȯ��
	
	DWORD UnitByte = 22;
	DWORD TmpSize;
	DWORD Total = 0;

	std::string Tmp(UnitByte,'\0');

	
	std::cout << "������ ������ : " << FileSize.QuadPart << std::endl;

	while (true) {



		std::string Name, Phone;

		if (!ReadFile(srcFile, &Tmp[0], UnitByte, &TmpSize, nullptr)) {
			std::cout << "���� �б� ����" << std::endl;
			CloseHandle(srcFile);
			
			return;
		}
		
		std::string check=std::string(Tmp);
		std::istringstream iss(check);

		Total += TmpSize;

		iss >> Name >> Phone;

		

		AddNewNode(Name, Phone);
		if (Total == FileSize.QuadPart) {
			std::cout << "���� ó���� �������ϴ�." << std::endl;
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
		std::cout << "����Ʈ�� �������� �ʽ��ϴ�." << std::endl;
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
	std::cout << "���� �Ϸ�" << std::endl;


}

void UserList::parseData(const char* data)
{
	std::string name, phone; // �̸��� ��ȭ��ȣ�� ������ ����
	const char* tokenStart = data; // ���� ��ū(�ʵ�)�� ����
	const char* p = data; // �����͸� ��ȸ�ϴ� ������

	while (*p) { // �� ���ڸ� ���� ������ �ݺ�
		if (*p == ' ') { // �ʵ� �����ڸ� ������ (�̸��� ��ȭ��ȣ ����)
			name.assign(tokenStart, p - tokenStart); // �̸� ����
			tokenStart = p + 1; // ��ū ������ ���� ��ġ�� ������Ʈ
		}
		else if (*p == '\n') { // ���ڵ� �����ڸ� ������ (�� ������ ��)
			phone.assign(tokenStart, p - tokenStart); // ��ȭ��ȣ ����
			AddNewNode(new UserData(name,phone)); // ������ �̸��� ��ȭ��ȣ�� �� ��� �߰�

			// ���� ���ڵ� ó���� ���� ���� �ʱ�ȭ
			name = "";
			phone = "";
			tokenStart = p + 1;
		}
		++p; // ������ �̵�
	}

	// ���� ���� �������� �� ������ ���ڵ� ó��
	if (p != tokenStart) {
		phone.assign(tokenStart, p - tokenStart); // ������ ��ȭ��ȣ ����
		AddNewNode(new UserData(name,phone)); // ������ ���ڵ忡 ���� ó��
	}
}
