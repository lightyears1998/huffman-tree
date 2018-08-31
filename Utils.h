#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ��ʾָ���ļ��Ķ����Ʊ���
void DumpBinary(string filename);

// ��ָ���ļ��Ķ����Ʊ��뱣�浽�ض��ļ�
void DumpAndSaveBinary(string filename, string savename);

// ����DumpAndSaveBinary����Ķ����Ʊ���ת��Ϊԭʼ�ļ�
void RecoverFromBinary(string savename, string filename);

#endif // UTILS_H_
