#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include "Utils.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <queue>

using namespace std;

// 哈夫曼树中的节点
struct HuffmanTreeNode
{
	int frequency;                                       // 节点的频率
	uint32_t code;                                       // 节点的哈夫曼编码
	unsigned char ch;                                    // 节点的原始编码
	HuffmanTreeNode *parent, *left_child, *right_child;  // 节点属性

	// 使用频率、哈夫曼编码和字符构造节点
	HuffmanTreeNode(int frequency, uint32_t code, unsigned char ch, HuffmanTreeNode * parent = nullptr, HuffmanTreeNode *left_child = nullptr, HuffmanTreeNode * right_child = nullptr)
	{
		this->frequency = frequency;
		this->code = 0, this->ch = ch;
		this->parent = parent, this->left_child = left_child, this->right_child = right_child;
	}

	// 合并两个节点为新节点
	HuffmanTreeNode(HuffmanTreeNode *lhs, HuffmanTreeNode *rhs)
	{
		frequency = lhs->frequency + rhs->frequency;
		code = 0, ch = 0;
		parent = nullptr, lhs->parent = rhs->parent = this;
		left_child = lhs, right_child = rhs;
	}

	~HuffmanTreeNode()
	{
		if (left_child != nullptr) delete left_child;
		if (right_child != nullptr) delete right_child;
		left_child = right_child = nullptr;
	}
};

// 此结构体用于以 CompareNodeByFrequency(HuffmanTreeNode * a, HuffmanTreeNode *b) 的形式排序节点
// 频率较高的节点优先于频率较低的节点
// 即 Comp(a, b) 当 (a->frequency) < (b->frequency) 时返回true
struct CompareNodeByFrequency
{
	bool operator()(const HuffmanTreeNode * lhs, const HuffmanTreeNode * rhs)
	{
		return lhs->frequency > rhs->frequency;
	}
};

// 表示一棵哈夫曼树
struct HuffmanTree
{
	HuffmanTreeNode * root;                 // 不为空时指向哈夫曼编码树的根节点
	map<uint32_t, unsigned char> code2ch;   // 从哈夫曼编码到字符的映射
	map<unsigned char, uint32_t> ch2code;   // 从字符到哈夫曼编码的映射
	string content;                         // 原始文件内容，原始文件是指未经过哈夫曼编码压缩的文件

	// 初始化一棵空哈夫曼树
	HuffmanTree()
	{
		root = nullptr;
	}

	~HuffmanTree()
	{
		delete root; root = nullptr;
	}

	// 从原始文件生成哈夫曼树，建立编码字符映射表
	void BuildFromSourceFile(string filename)
	{
		delete root; root = nullptr;
		code2ch.clear(), ch2code.clear();
		content.clear();

		ifstream src(filename, ios::binary);
		if (!src.is_open()) {
			cerr << "无法打开指定的文件：" + filename << endl;
			return;
		}

		map<unsigned char, int> frequency;  // 频率统计表

		unsigned char buff;
		while (src.read(reinterpret_cast<char *>(&buff), 1)) {
			frequency[buff]++;
			content += buff;
		}
		
		priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, CompareNodeByFrequency> que;  // 用于构建哈夫曼树的优先队列
		for (auto it : frequency)
		{
			HuffmanTreeNode * node = new HuffmanTreeNode(it.second, 0, it.first);
			que.push(node);
		}

		while (que.size() > 1)
		{
			HuffmanTreeNode * lhs = que.top(); que.pop();
			HuffmanTreeNode * rhs = que.top(); que.pop();
			HuffmanTreeNode * combine = new HuffmanTreeNode(lhs, rhs);
			que.push(combine);
		}
		
		root = que.top(); que.pop();
		CodeNodes();
	}

	// 从压缩文件中构建哈夫曼树，恢复字符映射表和原始文件内容
	void BuildFromCompactFile(string filename)
	{
		delete root; root = nullptr;
		code2ch.clear(), ch2code.clear();
		content.clear();

		ByteInputStream in(filename);
		
		uint32_t map_size = uint32_t(in.ReadCode());
		while (map_size--)
		{
			uint32_t code = in.ReadCode();
			unsigned char ch = in.ReadByte();
			code2ch[code] = ch;
			ch2code[ch] = code;
		}

		while (in.HasNext())
		{
			uint32_t buff = in.Get();
			if (in.HasNext())
			{
				if (code2ch.count(buff))
				{
					content += code2ch[buff];
					in.Clear();
				}
			}
		}
	}

	// 生成压缩文件
	void GenerateCompactFile(string saveto)
	{
		istringstream ss(content, ios::binary);
		ByteOutputStream out(saveto);

		uint32_t map_size = uint32_t(code2ch.size());  // 输出树的大小
		out.PutCode(map_size);

		for (auto it : code2ch)  // 输出树的结构
		{
			out.PutCode(it.first);
			out.PutByte(it.second);
		}

		unsigned char buff;
		while (ss.read(reinterpret_cast<char *>(&buff), 1))
		{
			out.Put(ch2code[buff]);
		}
		out.Close();
	}

	// 恢复原始文件
	void RetrieveSource(string saveto)
	{
		ofstream out(saveto, ios::binary);
		out << content;
	}

	// 建立树的结构后为树中的节点生成的哈夫曼编码
	void CodeNodes()
	{
		root->code = 1;
		CodeNodes(root);
	}

	// 为特定森林生成哈夫曼编码
	void CodeNodes(HuffmanTreeNode *node)
	{
		if (node->left_child) {
			node->left_child->code = ((node->code) << 1);
			CodeNodes(node->left_child);
		}
		if (node->right_child) {
			node->right_child->code = ((node->code) << 1) | 1;
			CodeNodes(node->right_child);
		}

		if (node->left_child == nullptr && node->right_child == nullptr)
		{
			code2ch[node->code] = node->ch;
			ch2code[node->ch] = node->code;
		}
	}

	// 向控制台打印哈夫曼编码
	void DumpCode()
	{
		cout << "ch+code\t";
		DumpCode(root);
	}

	// 向控制台打印特定特定森林中的所有节点的哈夫曼编码
	void DumpCode(HuffmanTreeNode *node)
	{
		if (node->left_child)
			DumpCode(node->left_child);
		if (node->right_child)
			DumpCode(node->right_child);
		if (node->left_child == nullptr && node->right_child == nullptr)
		{
			cout << hex << unsigned(node->ch) << '+' << node->code << '\t';
		}
	}
};

// 利用哈夫曼编码压缩文件
void Encode(string filename, string saveto);

// 解压哈夫曼编码压缩的文件
void Decode(string filename, string saveto);

#endif // !HUFFMANTREE_H_
