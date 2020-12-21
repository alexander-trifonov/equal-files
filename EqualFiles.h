#pragma once
#include <unordered_map>
#include <map>

#include "boost/filesystem.hpp"

#include <windows.h>
#include "cryptlib.h"
#include "files.h"
#include "sha.h"
#include "hex.h"

using namespace std;
using namespace boost::filesystem;

class EqualFiles
{
	boost::filesystem::path d1;
	boost::filesystem::path d2;
public:
	EqualFiles(boost::filesystem::path _d1, boost::filesystem::path _d2) 
	{
		d1 = _d1;
		d2 = _d2;
	};

	map<string, vector<path> > FindDuplicates()
	{
		map<string, vector<path> > sha1;
		map<int, vector<path>> filesizes;
		try //if path doesn't exists, it'll say
		{
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
			int count = 0;
			for (auto& fs_item : filesizes)
			{
				count++;
				if (fs_item.second.size() > 1)
				{
					cout << count << "/" << filesizes.size() << "\tsize:" << fs_item.first / (8 * 1024) << "KB" << endl; //Yes, it affects time measurement, but it's for User Experience.
					///Found more than 1 file with same size
					for (auto& p : fs_item.second)
					{
						//CryptoPP::MD5 hash;
						CryptoPP::SHA1 hash;
						string digest = "";
						//Calculate sha1 hash for the file and put into "sha1" table
						CryptoPP::FileSource f(p.string().c_str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
						sha1[digest].push_back(p);
					}
				}
			}
			for (auto& _path : sha1)
			{
				if (_path.second.size() == 1)
					sha1.erase(_path.first);
			}
			return sha1;
		}
		catch (const filesystem_error& e)
		{
			cout << e.what() << endl;
		}
	}
};