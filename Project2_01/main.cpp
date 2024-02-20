#include "Manager.h"

#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

using namespace std;

int main() {

	Manager manager(3); //value is order of bptree 
	manager.run("command.txt");

	_CrtDumpMemoryLeaks();
	return 0;
}

