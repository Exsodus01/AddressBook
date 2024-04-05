#include "UserInterface.h"
#include <iostream>
#include "UserList.h"
UserInterface::UserInterface(UserList& rList) //������ ������ �ʱ�ȭ ������� �ʱ�ȭ
	:List(rList)
{

}

UserInterface::~UserInterface()
{
}

void UserInterface::Add()
{
	std::string str, Pho;
	std::cout << "�Է��� �̸��� ��ȣ�� �̸� ��ȣ(0000-0000-0000)�������� �Է��ϼ���." << std::endl;
	std::cin >> str >> Pho;

	List.AddNewNode(str, Pho);

	std::cout << "�Է��� �Ϸ�Ǿ����ϴ�." << " ���� ��� ���� : " << UserData::GetUserDataCount() << std::endl;
}

void UserInterface::Search()
{
	std::string str;
	std::cout << "ã�� �̸��� �Է��ϼ���." << std::endl;
	std::cin >> str;

	List.FindNode(str);

}

void UserInterface::RemoveN()
{
	std::string str;
	std::cout << "������ �̸��� �Է��ϼ���." << std::endl;
	std::cin >> str;

	List.RemoveNode(str);
	std::cout << "������ �Ϸ�Ǿ����ϴ�." << "���� ��� ���� : " << UserData::GetUserDataCount() << std::endl;
}

int UserInterface::PrintUI()
{
	int tmp = 0;
	std::cout <<"0.exit" << "\n" << "1.Add" << "\n" << "2.Search" << "\n" << "3.Remove ���" << "\n" << "4.Remove ����Ʈ" << "\n" << "5.Print All" <<"\n"<<"6.LoadFile" << std::endl;
	std::cout << "�ʿ��� ��ȣ�� �Է��ϼ���" << std::endl;

	std::cin >> tmp;
	return tmp;
}

int UserInterface::Run()
{
	int Menu = 0;
	while ((Menu = PrintUI()) != 0) {
		switch (Menu) {

		case 1:
			Add();
			break;

		case 2:
			Search();
			break;

		case 3:
			RemoveN();
			break;

		case 4:
			RemoveL();
			break;

		case 5:
			PrintList();
			break;

		case 6:
			LoadF();
			break;

		default :
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << std::endl;

		}
	}




	return 0;
}

void UserInterface::PrintList()
{
	List.PrintAll();
}

void UserInterface::RemoveL()
{
	List.Clear();

	std::cout << "����Ʈ�� ������ ���� �Ǿ����ϴ�." << " ���� ��� ���� : " << UserData::GetUserDataCount() << std::endl;

}

void UserInterface::LoadF()
{
	List.LoadFile();
}
