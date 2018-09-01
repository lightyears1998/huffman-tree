#include "HuffmanTree.h"

// ���ù������������ѹ��
void Encode(string filename, string saveto)
{
	HuffmanTree tree;
	tree.BuildFromSourceFile(filename);
	tree.GenerateCompactFile(saveto);
}

// ��ѹ����������ѹ�����ļ�
void Decode(string filename, string saveto)
{
	HuffmanTree tree;
	tree.BuildFromCompactFile(filename);
	tree.RetrieveSource(saveto);
}
