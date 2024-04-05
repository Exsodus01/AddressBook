#include <iostream>
#include "UserInterface.h"
#include "UserList.h"

int main() {



	UserList DB;
	UserInterface UI(DB);
	UI.Run();





	return 0;
}