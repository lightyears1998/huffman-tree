#include "Utils.h"

void DumpBinary(string filename)
{
	cout << DumpBinaryToString(filename);
}

string DumpBinaryToString(string filename)
{
	ifstream in(filename, ios::binary);
	stringstream out;
	out.fill('0');

	unsigned char buff;
	while (in.read(reinterpret_cast<char *>(&buff), 1))
	{
		out << hex << setw(2) << unsigned(buff) << ' ';
	}
	return out.str();
}

void DumpBinaryToFile(string filename, string savename)
{
	ofstream(savename) << DumpBinaryToString(filename);
}

void RecoverFromBinaryFile(string savename, string filename)
{
	string binary;
	getline(ifstream(savename), binary);
	RecoverFromBinaryString(binary, filename);
}

void RecoverFromBinaryString(string binary, string filename)
{
	stringstream src(binary);
	ofstream out(filename, ios::binary);

	unsigned buff;
	while (src >> hex >> buff)
	{
		out << unsigned char(buff);
	}
}
