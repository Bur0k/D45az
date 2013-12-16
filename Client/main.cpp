#include <iostream>
#include "Client.h"

using namespace std;


void OnNewMessage(short id,vector<char> data)
{
	std::cout<<"ID:"<<id<<"\nData:\n";
	for(unsigned int i=0;i<data.size();i++)
		std::cout<<data[i];
	std::cout<<"\nEnde Packet\n\n";

}

#ifndef _DEBUG
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow ) //Release Mode verwenden wir Windows als SubSystem
#else
int main()//Im Debug Mode verwenden wir Console als SubSystem. Es wird trotzdem das SFML Fenster erzeugt.
#endif
{
	cout << "Hallo D45az" << endl;

	vector<char> blubb ;
	blubb.push_back('a');
	blubb.push_back('b');
	blubb.push_back('c');
	blubb.push_back(0);


	Client test;
	test.connectToServer("127.0.0.1",4242);
	test.newMessageCallback.push_back(OnNewMessage);
	test.beginRead();
	test.write(1,blubb);
	Sleep(1000);
	test.write(1,blubb);
	Sleep(1000);
	blubb.pop_back();
	blubb.push_back('C');
	blubb.push_back('B');
	blubb.push_back('A');
	blubb.push_back(0);
	test.write(42,blubb);

	getchar();
	return 0;
}