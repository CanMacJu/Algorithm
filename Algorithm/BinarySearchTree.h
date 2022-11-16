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

	void Insert(int key);


private:

	Node* _root = nullptr;

};

