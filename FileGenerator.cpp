#include <fstream>
#include <random>

using namespace std;

// https://github.com/alexander-trifonov/similar-strings/blob/master/FileGenerator.cpp
// [ Single-thread variant ]

void GenerateFile(unsigned short int lenmin = 3, unsigned short int lenmax = 7, unsigned int amount = 1000, string filename = "input.txt")
{
	random_device rd; //uses device or smth with low amount of entropy to generate a value, so use only for seed
	mt19937 engine(rd());
	//uniform_int_distribution<unsigned __int8> distChar(0, 25); //int8_t, and uint8_t are not allowed :(
	uniform_int_distribution<unsigned short int> distChar(0, 25); //|abcdefghijklmnopqrstuvwxyz|==26 
	uniform_int_distribution<unsigned short int> distLength(lenmin, lenmax); //for string's length; probably should use somthing simplier
	ofstream f_stream(filename, ofstream::trunc);

	unsigned short int length; //out of loop to not waste time on the initialization
	unsigned short int a = int('a');
	string _string;
	for (unsigned int i = 0; i < amount; i++)
	{
		length = distLength(engine);
		_string.clear();
		for (unsigned short int j = 0; j < length; j++)
		{
			_string += char(a + distChar(engine));
		}
		f_stream << _string << endl;
	}
	f_stream.close();
}
