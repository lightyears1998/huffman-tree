#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

// 在标准输出流中显示指定文件的二进制编码
// filename - 欲显示二进制编码的文件
void DumpBinary(const string& filename);

// 返回指定文件的二进制编码
// filename - 返回此文件的二进制编码
string DumpBinaryToString(const string& filename);

// 将指定文件的二进制编码保存到指定文件
// filename - 指定欲保存二进制编码的文件
// savename - 指定用于保存二进制编码的文件
void DumpBinaryToFile(const string& filename, const string& savename);

// 从保存二进制编码的文件中恢复原始文件
// savename - 保存二进制编码的文件名
// filename - 原始文件以此文件名储存
void RecoverFromBinaryFile(const string& savename, const string& filename);

// 从二进制编码字符串中恢复原始文件
// binary - 二进制编码字符串
// filename - 原始文件以此文件名储存
void RecoverFromBinaryString(const string& binary, const string& filename);

#endif // UTILS_H_
