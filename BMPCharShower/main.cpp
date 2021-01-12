#include "BmpReader.h"
#include "CharShower.h"
#include "ConsoleController.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int main()
{
	ConsoleController ccr;
	::system("cls");

	constexpr int nums = 450;
	vector<ostringstream> chars(nums);

	for (int i = 0; i < nums; ++i)
	{
		string fileName = "img\\test" + to_string(i) + ".bmp";
		CharShower c(fileName, 48, 70, chars[i]);
		c.Print();
		cout << "image: " << i << "is ready!" << endl;
	}

	::system("cls");
	cout << "Prepared!" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	::system("cls");
	for (int i = 1; i > 0; --i)
	{
		ccr.SetCursorPos(0, 0);
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}

	for (int i = 0; i < nums; ++i)
	{
		auto beginTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		ccr.SetCursorPos(0, 0);
		cout << chars[i].str() << flush;
		auto endTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		this_thread::sleep_for(chrono::milliseconds((40 - (endTime - beginTime)) > 0 ? (40 - (endTime - beginTime)) : 0));
	}

	this_thread::sleep_for(chrono::seconds(2));
	
	cin.get();
	return 0;
}

//auto beginTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
