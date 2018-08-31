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
	tr.BuildFromSourceFile("Sample.txt");
	tr.DumpCode();
	tr.GenerateCompactFile("Sample.CHEX.txt");
	tr.RetrieveSource("Sample.R.txt");
}
