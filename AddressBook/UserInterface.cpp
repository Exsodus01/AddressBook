#include "UserInterface.h"
#include "UserData.h"
#include <iostream>
#include <chrono>

#include "UserList.h"
#include <unordered_map>
CRITICAL_SECTION CriticalSection;
std::unordered_map<int, bool> function_status;
UserInterface::UserInterface(UserList& rList) //참조는 생성자 초기화 목록으로 초기화
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
	std::cout << "입력한 이름과 번호를 이름 번호(0000-0000-0000)형식으로 입력하세요." << std::endl;
	std::cin >> str >> Pho;
	auto start = std::chrono::high_resolution_clock::now();
//	List.AddNewNode(str, Pho);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 밀리초 단위로 변환

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;

	std::cout << "입력이 완료되었습니다." << " 남은 노드 개수 : " << UserData::GetUserDataCount() << std::endl;
}

void UserInterface::Search()
{
	std::cout << '\n' << '\n';
	std::string str;
	std::cout << "찾을 이름을 입력하세요." << std::endl;
	std::cin >> str;
	auto start = std::chrono::high_resolution_clock::now();
	List.FindNode(str);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 밀리초 단위로 변환

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;

}

void UserInterface::RemoveN()
{
	std::cout << '\n' << '\n';
	std::string str;
	std::cout << "삭제할 이름을 입력하세요." << std::endl;
	std::cin >> str;

	auto start = std::chrono::high_resolution_clock::now();
	List.RemoveNode(str);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 밀리초 단위로 변환

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;
	std::cout << "삭제가 완료되었습니다." << "남은 노드 개수 : " << UserData::GetUserDataCount() << std::endl;
}

int UserInterface::PrintUI()
{
	std::cout << '\n' << '\n';
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

		case 7:
			//정렬 구현
			break;
		case 8:
			ModeChange();
			//멀티스레드 사용모드로 변경
			break;
		default :
			std::cout << "잘못된 값을 입력했습니다. 다시 입력하세요." << std::endl;

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
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 밀리초 단위로 변환

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;
	std::cout << "전체 노드의 개수 : " << UserData::GetUserDataCount() << std::endl;
}

void UserInterface::RemoveL()
{

	std::cout << '\n' << '\n';
	auto start = std::chrono::high_resolution_clock::now();
	List.Clear();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 밀리초 단위로 변환

	std::cout << "Function took " << duration << " milliseconds to complete." << std::endl;

	std::cout << "리스트가 완전히 삭제 되었습니다." << " 남은 노드 개수 : " << UserData::GetUserDataCount() << std::endl;

}

void UserInterface::LoadF()
{
	std::cout << '\n' << '\n';
	auto start = std::chrono::high_resolution_clock::now();
	List.LoadFile();
	auto end = std::chrono::high_resolution_clock::now(); 
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 밀리초 단위로 변환

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
			// 함수 실행...
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
				//정렬 구현
				break;
			case 8:
				//멀티스레드 사용모드로 변경
				break;
			default:
				std::cout << "잘못된 값을 입력했습니다. 다시 입력하세요." << std::endl;
			}

			EnterCriticalSection(&CriticalSection);
			function_status[function_Num] = false;
			LeaveCriticalSection(&CriticalSection);

			std::cout << "Function " << function_Num << " is now idle." << std::endl;
			});

	}

}