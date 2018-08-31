#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

// 在标准输出流中显示指定文件的二进制编码
// 参数filename - 欲显示二进制编码的文件
void DumpBinary(string filename);

// 返回指定文件的二进制编码
string DumpBinaryToString(string filename);

// 将指定文件的二进制编码保存到指定文件
// 参数filename - 欲保存二进制编码的文件
// 参数savename - 指定用于保存二进制编码的文件
void DumpBinaryToFile(string filename, string savename);

// 将由DumpBinaryToFile()输出的二进制编码转换为原始文件
// 参数savename - 保存的二进制编码文件名
void RecoverFromBinaryFile(string savename, string filename);

void RecoverFromBinaryString(string binary, string filename);

#endif // UTILS_H_
