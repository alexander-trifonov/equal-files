#include <iostream>
#include "EqualFiles.h"
#include <chrono> //time measurement

//Boost: to remember how to use 3rd party libraries
#include "boost/filesystem.hpp"
//boost was built in MT runtime: b2.exe address-model=64 runtime-link=static architecture=x86 release

using namespace std;
using namespace boost::filesystem;

void main(int argc, char* argv[])
{
	chrono::steady_clock::time_point time_start;
	chrono::steady_clock::time_point time_end;

	path d1;
	path d2;

	// [ Input ]
	if (argc > 2)
	{
		d1 = argv[1];
		d2 = argv[2];
	}
	else
	{
		string answer;
		while (true)
		{
			cout << "Write paths to directories:\n";
			cout << "1: ";
			getline(cin, answer);
			d1 = answer;
			cout << "2: ";
			getline(cin, answer);
			d2 = answer;
			break;
		}
	}

	// [ Hashing and Output ]
	cout << "\n[[ Hashing ]]\n";
	EqualFiles object(d1, d2);
	time_start = chrono::steady_clock::now();
	auto sha1 = object.FindDuplicates();
	time_end = chrono::steady_clock::now();
	//Display dublicated files
	cout << "\n[[ Found Dublicated Files ]]\n";
	cout << "Done in: " << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << "ms\n";
	bool found = false;
	for (auto& item : sha1)
	{
		//if we found more than 1 files with same hash
		if (item.second.size() > 1)
		{
			found = true;
			cout << "File size: " << file_size(item.second[0]) << " bytes\n" << "SHA1: " << item.first << endl;
			for (auto& _path : item.second)
			{
				cout << "\t" << _path << endl;
			}
		}
	}
	if (!found)
	{
		cout << "None files have been found\n";
	}
	cout << "Done in: " << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << "ms\n";

}