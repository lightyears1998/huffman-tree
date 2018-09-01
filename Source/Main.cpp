#include "Utils.h"
#include "HuffmanTree.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

int main(int argc, char * argv[])
{
	Encode("Sample/Sample.txt", "Temp/s.txt");
	Decode("Temp/s.txt", "Temp/o.txt");
}
