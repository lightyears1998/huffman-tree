#include "Utils.h"

void DumpBinary(const string& filename)
{
	cout << DumpBinaryToString(filename);
}

string DumpBinaryToString(const string& filename)
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

void DumpBinaryToFile(const string& filename, const string& savename)
{
	ofstream(savename) << DumpBinaryToString(filename);
}

void RecoverFromBinaryFile(const string& savename, const string& filename)
{
	string binary;
	getline(ifstream(savename), binary);
	RecoverFromBinaryString(binary, filename);
}

void RecoverFromBinaryString(const string& binary, const string& filename)
{
	stringstream src(binary);
	ofstream out(filename, ios::binary);

	unsigned buff;
	while (src >> hex >> buff)
	{
		out << unsigned char(buff);
	}
}
