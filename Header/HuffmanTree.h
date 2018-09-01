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

struct Node
{
	int frequency;                            // �ڵ��Ƶ��
	uint32_t code;                            // �ڵ�Ĺ���������
	unsigned char ch;                         // �ڵ��ԭʼ����
	Node *parent, *left_child, *right_child;  // �ڵ�����

	Node(int frequency, uint32_t code, unsigned char ch, Node * parent = nullptr, Node *left_child = nullptr , Node * right_child = nullptr)
	{
		this->frequency = frequency;
		this->code = 0, this->ch = ch;
		this->parent = parent, this->left_child = left_child, this->right_child = right_child;
	}

	Node(Node *lhs, Node *rhs)
	{
		frequency = lhs->frequency + rhs->frequency;
		code = 0, ch = 0;
		parent = nullptr, lhs->parent = rhs->parent = this;
		left_child = lhs, right_child = rhs;
	}

	~Node()
	{
		if (left_child != nullptr) delete left_child;
		if (right_child != nullptr) delete right_child;
	}
};

// ����Node *������
struct CompareNodeByFrequency
{
	bool operator()(const Node * lhs, const Node * rhs)
	{
		return lhs->frequency > rhs->frequency;
	}
};

struct HuffmanTree
{
	Node * root;
	map<uint32_t, unsigned char> code2ch;
	map<unsigned char, uint32_t> ch2code;
	string content;  // �ļ���ԭʼ����

	HuffmanTree()
	{
		root = nullptr;
	}

	~HuffmanTree()
	{
		delete root; root = nullptr;
	}

	// ��Դ�ļ��й�����������
	void BuildFromSourceFile(string filename)
	{
		delete root; root = nullptr;
		content.clear();

		ifstream src(filename, ios::binary);

		map<unsigned char, int> frequency;

		unsigned char buff;
		while (src.read(reinterpret_cast<char *>(&buff), 1)) {
			frequency[buff]++;
			content += buff;
		}
		
		priority_queue<Node*, vector<Node*>, CompareNodeByFrequency> que;
		for (auto it : frequency)
		{
			Node * node = new Node(it.second, 0, it.first);
			que.push(node);
		}

		while (que.size() > 1)
		{
			Node * lhs = que.top(); que.pop();
			Node * rhs = que.top(); que.pop();
			Node * combine = new Node(lhs, rhs);
			que.push(combine);
		}
		
		root = que.top(); que.pop();
		CodeNodes();
	}

	// ��ѹ���ļ��й�����������
	void BuildFromCompactFile(string filename)
	{
		delete root; root = nullptr;
		content.clear();
		code2ch.clear(), ch2code.clear();

		// ofstream out("Temp/out.txt", ios::binary);

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

	// ����ѹ���ļ�
	void GenerateCompactFile(string saveto)
	{
		istringstream ss(content, ios::binary);
		ByteOutputStream out(saveto);

		uint32_t map_size = uint32_t(code2ch.size());  // ������Ĵ�С
		out.PutCode(map_size);

		for (auto it : code2ch)  // ������Ľṹ
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

	// �ָ�ԭʼ�ļ�
	void RetrieveSource(string saveto)
	{
		ofstream out(saveto, ios::binary);
		out << content;
	}

	// �������Ľṹ��Ϊ���еĽڵ����ɵĹ���������
	void CodeNodes()
	{
		root->code = 1;
		CodeNodes(root);
	}

	// Ϊ�ض�ɭ�����ɹ���������
	void CodeNodes(Node *node)
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

	// �����̨��ӡ����������
	void DumpCode()
	{
		cout << "ch+code\t";
		DumpCode(root);
	}

	// �����̨��ӡ�ض��ض�ɭ���е����нڵ�Ĺ���������
	void DumpCode(Node *node)
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

// ���ù���������ѹ���ļ�
void Encode(string filename, string saveto);

// ��ѹ����������ѹ�����ļ�
void Decode(string filename, string saveto);

#endif // !HUFFMANTREE_H_
