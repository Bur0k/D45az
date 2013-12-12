#include <iostream>
#include "Client.h"

using namespace std;

#ifndef _DEBUG
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow ) //Release Mode verwenden wir Windows als SubSystem
#else
int main()//Debug Mode verwenden wir Console als SubSystem. Es wird trotzdem das SFML Fenster erzeugt.
#endif
{
	cout << "Hallo D45az" << endl;

	vector<char> blubb ;
	blubb.push_back('a');
	blubb.push_back('b');
	blubb.push_back('c');


	Client test;
	test.connectToServer("127.0.0.1",424242);
	test.write(1,blubb);
	test.write(42,blubb);
	test.write(1,blubb);
	test.write(1,blubb);

	getchar();
	return 0;
}