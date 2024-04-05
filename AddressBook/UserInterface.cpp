#include "UserInterface.h"
#include <iostream>
#include "UserList.h"
UserInterface::UserInterface(UserList& rList) //참조는 생성자 초기화 목록으로 초기화
	:List(rList)
{

}

UserInterface::~UserInterface()
{
}

void UserInterface::Add()
{
	std::string str, Pho;
	std::cout << "입력한 이름과 번호를 이름 번호(0000-0000-0000)형식으로 입력하세요." << std::endl;
	std::cin >> str >> Pho;

	List.AddNewNode(str, Pho);

	std::cout << "입력이 완료되었습니다." << " 남은 노드 개수 : " << UserData::GetUserDataCount() << std::endl;
}

void UserInterface::Search()
{
	std::string str;
	std::cout << "찾을 이름을 입력하세요." << std::endl;
	std::cin >> str;

	List.FindNode(str);

}

void UserInterface::RemoveN()
{
	std::string str;
	std::cout << "삭제할 이름을 입력하세요." << std::endl;
	std::cin >> str;

	List.RemoveNode(str);
	std::cout << "삭제가 완료되었습니다." << "남은 노드 개수 : " << UserData::GetUserDataCount() << std::endl;
}

int UserInterface::PrintUI()
{
	int tmp = 0;
	std::cout <<"0.exit" << "\n" << "1.Add" << "\n" << "2.Search" << "\n" << "3.Remove 노드" << "\n" << "4.Remove 리스트" << "\n" << "5.Print All" <<"\n"<<"6.LoadFile" << std::endl;
	std::cout << "필요한 번호를 입력하세요" << std::endl;

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
			std::cout << "잘못된 값을 입력했습니다. 다시 입력하세요." << std::endl;

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

	std::cout << "리스트가 완전히 삭제 되었습니다." << " 남은 노드 개수 : " << UserData::GetUserDataCount() << std::endl;

}

void UserInterface::LoadF()
{
	List.LoadFile();
}
