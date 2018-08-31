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
	DumpAndSaveBinary("Sample.txt", "Sample.HEX.txt");
	RecoverFromBinary("Sample.HEX.txt", "Sample.OUT.txt");
}
