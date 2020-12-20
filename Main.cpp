#include <iostream>
#include <map>
#include "FileGenerator.h"
#include <random> // for uniform distribution
#include <chrono> //time measurement

//Boost: to remember how to use 3rd party libraries
#include "boost/filesystem.hpp"
//boost was built in MT runtime: b2.exe address-model=64 runtime-link=static architecture=x86 release

//Crypto++: for hashing files fast (?)
#include <windows.h>
#include "cryptlib.h"
#include "files.h"
#include "sha.h"
#include "hex.h"

using namespace std;
using namespace boost::filesystem;

void main(int argc, char* argv[])
{
	chrono::steady_clock::time_point time_start;
	chrono::steady_clock::time_point time_end;
	//sha1.key	- sha1 hash
	//sha1.value - vector of files paths with sha1 hash as key
	map<string, vector<path> > sha1;
	map<int, vector<path>> filesizes;
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
		cout << "[ Files Generating ]\n";
		cout << "Generate N text files for a quick test?\n";
		string answer;
		while (true)
		{
			cout << "Y\\N: ";
			cin >> answer;
			if (answer == "Y")
			{
				int N, K;
				cout << "How many files generate in each folder (e.g. 15)?: ";
				cin >> N;
				cout << "Parameter for file's sizes (e.g. 2): ";
				cin >> K;
				try
				{
					remove_all("directory_1");
					remove_all("directory_2");
					create_directory("directory_1"); //throws exception sometimes #5
					create_directory("directory_2");
				}
				catch(filesystem_error& e)
				{
					cout << e.what() << endl;
				}
				//asdsad
				d1 = "directory_1";
				d2 = "directory_2";
				int min = K;
				int max = K + 2;
				std::random_device rd;     // only used once to initialise (seed) engine
				std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
				std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
				//Generating binary files, you can open them and see what's inside;
				cout << "[ Generating... ]\n";
				for (int i = 0; i < N; i++)
				{
					if (N < 20)
						cout << "Generating \"input" + to_string(i) + "\"...\n";
					GenerateFile(3, 5, pow(10, uni(rng)), "directory_1/input" + to_string(i));
					//cout << "Generating \"directory_2/input" + to_string(i) + "\"...\n";
					GenerateFile(3, 5, pow(10, uni(rng)), "directory_2/input" + to_string(i)); //completely different from directory_1
				}
				///Dublicating some files;
				cout << "\n[ Dublicating Files ]\n";
				int count = N / 3 + 1;
				//std::uniform_int_distribution<int> uni2(1, 3); //perhaps I can overuse "uni" variable, but I don't have enough time right now
				for (auto& item : recursive_directory_iterator(d1))
				{
					if (count == 0)
						break;
					cout << "Copying " << item.path() << " to \"" + d2.string() + "\"\\" << endl;
					copy_file(item.path(), path(d2.string() + "\\" + item.path().filename().string()), copy_option::overwrite_if_exists);
					count--;
				}
				break;
			}
			else if (answer == "N")
			{
				cout << "Write paths to directories:\n";				
				cout << "1: ";
				//cin >> answer;
				getline(cin, answer);
				getline(cin, answer);
				d1 = answer;
				cout << "2: ";
				//cin >> answer;
				getline(cin, answer);
				d2 = answer;
				break;
			}
		}
		//d1 = "D:\\temp\\d1";
		//d2 = "D:\\temp\\d2";
	}

	// [ Hashing and Output ]
	try //if path doesn't exists, it'll say
	{
		cout << "[ Hashing ]\n";
		time_start = chrono::steady_clock::now();
		//Loop through directories and map files sizes with paths;
		for (auto& item : recursive_directory_iterator(d1))
		{
			if (is_directory(item))
				continue;
			filesizes[file_size(item.path())].push_back(item.path());
		}
		for (auto& item : recursive_directory_iterator(d2))
		{
			if (is_directory(item))
				continue;
			filesizes[file_size(item.path())].push_back(item.path());
		}
		for (auto& fs_item : filesizes)
		{
			if (fs_item.second.size() > 1)
			{
				///Found more than 1 file with same size
				for (auto& p : fs_item.second)
				{
					CryptoPP::SHA1 hash;
					string digest = "";
					//Calculate sha1 hash for the file and put into "sha1" table
					CryptoPP::FileSource f(p.string().c_str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
					sha1[digest].push_back(p);
				}
			}
		}
		time_end = chrono::steady_clock::now();
		//Display dublicated files
		cout << "\n[ Found Dublicated Files ]\n";
		cout << "Done in: " << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << "ms\n";
		bool found = false;
		for (auto& item : sha1)
		{
			//if we wound more than 1 files with same hash
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
	catch(const filesystem_error& e)
	{
		cout << e.what() << endl;
	}



}