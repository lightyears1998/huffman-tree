#include "Utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;

int main(int argc, char * argv[])
{
	DumpBinaryToFile("Sample.txt", "Sample.HEX.txt");
	RecoverFromBinaryFile("Sample.HEX.txt", "Sample.OUT.txt");
}
