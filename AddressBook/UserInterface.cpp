#include "UserInterface.h"
#include "UserData.h"
#include <iostream>
#include <chrono>

#include "UserList.h"
#include <unordered_map>
CRITICAL_SECTION CriticalSection;
std::unordered_map<int, bool> function_status;
UserInterface::UserInterface(UserList& rList) //������ ������ �ʱ�ȭ ������� �ʱ�ȭ
	:List(rList)
{

}

UserInterface::~UserInterface()
{
}

void UserInterface::Add()
{
	std::cout << '\n' << '\n';
	std::string str, Pho;
	std::cout << "�Է��� �̸��� ��ȣ�� �̸� ��ȣ(0000-0000-0000)�������� �Է��ϼ���." << std::endl;
	std::cin >> str >> Pho;
	auto start = std::chrono::high_resolution_clock::now();
//	List.AddNewNode(str, Pho);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // �и��� ������ ��ȯ

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;

	std::cout << "�Է��� �Ϸ�Ǿ����ϴ�." << " ���� ��� ���� : " << UserData::GetUserDataCount() << std::endl;
}

void UserInterface::Search()
{
	std::cout << '\n' << '\n';
	std::string str;
	std::cout << "ã�� �̸��� �Է��ϼ���." << std::endl;
	std::cin >> str;
	auto start = std::chrono::high_resolution_clock::now();
	List.FindNode(str);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // �и��� ������ ��ȯ

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;

}

void UserInterface::RemoveN()
{
	std::cout << '\n' << '\n';
	std::string str;
	std::cout << "������ �̸��� �Է��ϼ���." << std::endl;
	std::cin >> str;

	auto start = std::chrono::high_resolution_clock::now();
	List.RemoveNode(str);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // �и��� ������ ��ȯ

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;
	std::cout << "������ �Ϸ�Ǿ����ϴ�." << "���� ��� ���� : " << UserData::GetUserDataCount() << std::endl;
}

int UserInterface::PrintUI()
{
	std::cout << '\n' << '\n';
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

		case 7:
			//���� ����
			break;
		case 8:
			ModeChange();
			//��Ƽ������ ������ ����
			break;
		default :
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << std::endl;

		}
	}




	return 0;
}

void UserInterface::PrintList()
{
	std::cout << '\n' << '\n';

	auto start = std::chrono::high_resolution_clock::now();
	List.PrintAll();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // �и��� ������ ��ȯ

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;
	std::cout << "��ü ����� ���� : " << UserData::GetUserDataCount() << std::endl;
}

void UserInterface::RemoveL()
{

	std::cout << '\n' << '\n';
	auto start = std::chrono::high_resolution_clock::now();
	List.Clear();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // �и��� ������ ��ȯ

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;

	std::cout << "����Ʈ�� ������ ���� �Ǿ����ϴ�." << " ���� ��� ���� : " << UserData::GetUserDataCount() << std::endl;

}

void UserInterface::LoadF()
{
	std::cout << '\n' << '\n';
	auto start = std::chrono::high_resolution_clock::now();
	List.LoadFile();
	auto end = std::chrono::high_resolution_clock::now(); 
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // �и��� ������ ��ȯ

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;
}

void UserInterface::ModeChange()
{

}



void UserInterface::Multithread(int function_Num, boost::asio::io_service& io)
{
	bool alreadyRunning = false;
	{
		EnterCriticalSection(&CriticalSection);
		if (function_status[function_Num]) {
			alreadyRunning = true;
			std::cout << "Function " << function_Num << " is already running." << std::endl;
		}
		else {
			function_status[function_Num] = true;
			std::cout << "Function " << function_Num << " is running." << std::endl;
		}
		LeaveCriticalSection(&CriticalSection);
	}

	if (!alreadyRunning) {
		io.post([function_Num]() {
			// �Լ� ����...
			switch (function_Num) {
			case 1:
				//Add();
				break;

			case 2:
				//Search();
				break;

			case 3:
			//	RemoveN();
				break;

			case 4:
				//RemoveL();
				break;

			case 5:
			//	PrintList();
				break;

			case 6:
			//	LoadF();
				break;

			case 7:
				//���� ����
				break;
			case 8:
				//��Ƽ������ ������ ����
				break;
			default:
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << std::endl;
			}

			EnterCriticalSection(&CriticalSection);
			function_status[function_Num] = false;
			LeaveCriticalSection(&CriticalSection);

			std::cout << "Function " << function_Num << " is now idle." << std::endl;
			});

	}

}