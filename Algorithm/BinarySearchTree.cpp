#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
#include <queue>

using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
	{
		return;
	}

	SetCursorPosition(x, y);
	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}


void BinarySearchTree::Print_Inorder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	Print_Inorder(node->left);
	cout << node->key << endl;
	Print_Inorder(node->right);
}


Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
	{
		return node;
	}

	if (key < node->key)
	{
		return Search(node->left, key);
	}
	else
	{
		return Search(node->right, key);
	}
}

Node* BinarySearchTree::SearchNonrecursive(Node* node, int key)
{
	while (node && key != node->key)
	{
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node && node->left)
	{
		node = node->left;
	}

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node && node->right)
	{
		node = node->right;
	}

	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right)
	{
		return Min(node->right);
	}

	Node* parent = node->parent;


	/*while (parent && parent->key < node->key)
	{
		parent = parent->parent;
	}*/
	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}


void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (node)
	{
		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	newNode->parent = parent;

	if (key < parent->key)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}

}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr)
	{
		Replace(node, node->right);
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}
	else
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// u 서브트리를 v 서브트리로 교체 후 delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	Node* parent = u->parent;
	if (parent == nullptr)
	{
		_root = v;
	}
	else if ( parent->left == u)
	{
		parent->left = v;
	}
	else
	{
		parent->right = v;
	}

	if (v)
	{
		v->parent = parent;
	}

	delete u;
}
