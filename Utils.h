#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// 向特定文件输出紧凑字节流的工具
struct ByteOutputStream
{
	unsigned char buff;
	int buff_count;
	ofstream out;

	ByteOutputStream(string filename) {
		buff = 0, buff_count = 0;
		out = ofstream(filename, ios::binary);
	}
	
	~ByteOutputStream() {
		Close();
	}

	void Close()
	{
		if (buff_count) {
			buff <<= (8 - buff_count);
			out << buff;
		}
		out.close();
	}

	int Count(uint32_t code)
	{
		int count = 0;
		while (code) {
			++count;
			code >>= 1;
		}
		return count;
	}

	void Put(uint32_t code)
	{
		int code_count = Count(code);
		code <<= 32 - code_count;
		while (code_count) {
			int diff = min(8 - buff_count, code_count);
			code_count -= diff, buff_count += diff;
			while (diff--) {
				buff <<= 1;
				if (code &(1U << 31)) {
					buff |= 1;
				}
				code <<= 1;
			}

			if (buff_count == 8) {
				out << buff;
				
				buff = 0, buff_count = 0;
			}
		}
	}
};

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
