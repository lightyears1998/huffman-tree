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
	HuffmanTree tr;
	tr.BuildFromSourceFile("Sample/Sample.txt");
	tr.DumpCode();
	tr.GenerateCompactFile("Sample/Sample.CHEX.txt");
	tr.BuildFromCompactFile("Sample/Sample.CHEX.txt");
}