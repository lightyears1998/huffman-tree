#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// 显示指定文件的二进制编码
void DumpBinary(string filename);

// 将指定文件的二进制编码保存到特定文件
void DumpAndSaveBinary(string filename, string savename);

// 将由DumpAndSaveBinary输出的二进制编码转换为原始文件
void RecoverFromBinary(string savename, string filename);

#endif // UTILS_H_
