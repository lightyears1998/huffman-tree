#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

// �ڱ�׼���������ʾָ���ļ��Ķ����Ʊ���
// ����filename - ����ʾ�����Ʊ�����ļ�
void DumpBinary(string filename);

// ����ָ���ļ��Ķ����Ʊ���
string DumpBinaryToString(string filename);

// ��ָ���ļ��Ķ����Ʊ��뱣�浽ָ���ļ�
// ����filename - ����������Ʊ�����ļ�
// ����savename - ָ�����ڱ�������Ʊ�����ļ�
void DumpBinaryToFile(string filename, string savename);

// ����DumpBinaryToFile()����Ķ����Ʊ���ת��Ϊԭʼ�ļ�
// ����savename - ����Ķ����Ʊ����ļ���
void RecoverFromBinaryFile(string savename, string filename);

void RecoverFromBinaryString(string binary, string filename);

#endif // UTILS_H_
