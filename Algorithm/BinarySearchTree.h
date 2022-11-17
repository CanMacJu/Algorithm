#pragma once


struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
};


class BinarySearchTree
{
public:

	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);

	void Print_Inorder(Node* node);
	void Print_Inorder() { Print_Inorder(_root); }

	Node* Search(Node* node, int key);
	Node* SearchNonrecursive(Node* node, int key);

	Node* Min() { return Min(_root); }
	Node* Min(Node* node);
	Node* Max() { return Max(_root); }
	Node* Max(Node* node);
	Node* Next() { return Next(_root); }
	Node* Next(Node* node);

	void Insert(int key);

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);

	Node* GetRootNode() { return _root; }

private:

	Node* _root = nullptr;

};

