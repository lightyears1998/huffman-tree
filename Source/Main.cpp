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
	Encode("Sample/Sample.txt", "压缩文件"); 
	Decode("压缩文件", "解压的文件.txt");
}
