#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ���ض��ļ���������ֽ����Ĺ���
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

	// ���4�ֽ�����
	void PutCode(uint32_t code)
	{
		out.write(reinterpret_cast<char *>(&code), 4);
	}

	// ������ֽ�����
	void PutByte(unsigned char ch)
	{
		out.write(reinterpret_cast<char *>(&ch), 1);
	}
};

// ���ض��ļ��ж�ȡ�����ֽ����Ĺ���
struct ByteInputStream
{
	ifstream in;
	uint32_t cache;
	unsigned char buff;
	int buff_count;

	ByteInputStream(string filename)
	{
		in = ifstream(filename, ios::binary);
		cache = 0, buff = 0;
		buff_count = 0;
	}

	// ��ȡ��һ������
	uint32_t Get()
	{
		if (!buff_count) {
			in.read(reinterpret_cast<char *>(&buff), 1);
			buff_count = 8;
		}
		cache <<= 1;
		cache |= (buff & (1U << 7)?1:0);
		buff <<= 1;
		--buff_count;
		return cache;
	}

	// ��ȡ���ֽ�����
	unsigned char ReadByte()
	{
		if (!in.is_open()) return 0;

		unsigned char buff;
		in.read(reinterpret_cast<char *>(&buff), 1);
		return buff;
	}

	// ��ȡ4�ֽ�����
	uint32_t ReadCode()
	{
		if (!in.is_open()) return 0;

		uint32_t buff;
		in.read(reinterpret_cast<char *>(&buff), 4);
		return buff;
	}

	// ���������Ƿ�����ʣ���ֽ�
	bool HasNext()
	{
		return !in.eof();
	}
	
	// ��������λ
	void Clear() {
		cache = 0;
	}
};

// �ڱ�׼���������ʾָ���ļ��Ķ����Ʊ���
// filename - ����ʾ�����Ʊ�����ļ�
void DumpBinary(const string& filename);

// ����ָ���ļ��Ķ����Ʊ���
// filename - ���ش��ļ��Ķ����Ʊ���
string DumpBinaryToString(const string& filename);

// ��ָ���ļ��Ķ����Ʊ��뱣�浽ָ���ļ�
// filename - ָ������������Ʊ�����ļ�
// savename - ָ�����ڱ�������Ʊ�����ļ�
void DumpBinaryToFile(const string& filename, const string& savename);

// �ӱ�������Ʊ�����ļ��лָ�ԭʼ�ļ�
// savename - ��������Ʊ�����ļ���
// filename - ԭʼ�ļ��Դ��ļ�������
void RecoverFromBinaryFile(const string& savename, const string& filename);

// �Ӷ����Ʊ����ַ����лָ�ԭʼ�ļ�
// binary - �����Ʊ����ַ���
// filename - ԭʼ�ļ��Դ��ļ�������
void RecoverFromBinaryString(const string& binary, const string& filename);

#endif // UTILS_H_
