
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() {}
	Node(const string& data) : data(data) {}

	string data;

	vector<NodeRef> children;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
	}

	return root;
}

void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		cout << "--";
	}
	cout << root->data << endl;

	for (auto child : root->children)
	{
		PrintTree(child, depth + 1);
	}
}

int GetHeight(NodeRef root)
{
	int Height = 1;
	for (auto child : root->children)
	{
		if (Height < GetHeight(child) + 1)
		{
			Height = GetHeight(child) + 1;
		}

		Height = max(Height, GetHeight(child) + 1);
	}

	return Height;
}

int main()
{
	NodeRef root = CreateTree();

	PrintTree(root, 0);

	cout << GetHeight(root) << endl;

	return 0;
}