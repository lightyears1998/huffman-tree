#include "Utils.h"

void DumpBinary(string filename)
{
	ifstream in(filename, ios::binary);
	
	unsigned char buff;
	char org = cout.fill('0');
	while (in.read(reinterpret_cast<char *>(&buff), 1))
	{
		cout << hex << setw(2) << setfill('0') << unsigned(buff) << ' ';
	}
	cout.fill(org);
}

void DumpAndSaveBinary(string filename, string savename)
{
	ifstream in(filename, ios::binary);
	ofstream out(savename);
	out.fill('0');
	
	unsigned char buff;
	while (in.read(reinterpret_cast<char *>(&buff), 1))
	{
		out << hex << setw(2) << unsigned(buff) << ' ';
	}
}

void RecoverFromBinary(string savename, string filename)
{
	ifstream in(savename);
	ofstream out(filename, ios::binary);

	unsigned buff;
	while (in >> hex >> buff)
	{
		out << unsigned char(buff);
	}
}
