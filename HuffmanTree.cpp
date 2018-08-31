#include "HuffmanTree.h"

void Encode(string filename, string saveto)
{
	HuffmanTree tree;
	tree.BuildFromSourceFile(filename);
	tree.GenerateCompactFile(saveto);
}

void Decode(string filename, string saveto)
{
	HuffmanTree tree;
	tree.BuildFromCompactFile(filename);
	tree.RetrieveSource(saveto);
}
