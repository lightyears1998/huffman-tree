#include "HuffmanTree.h"

// 利用哈夫曼编码进行压缩
void Encode(string filename, string saveto)
{
	HuffmanTree tree;
	tree.BuildFromSourceFile(filename);
	tree.GenerateCompactFile(saveto);
}

// 解压哈夫曼编码压缩的文件
void Decode(string filename, string saveto)
{
	HuffmanTree tree;
	tree.BuildFromCompactFile(filename);
	tree.RetrieveSource(saveto);
}
