#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

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
