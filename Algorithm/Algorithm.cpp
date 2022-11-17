
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>
#include "BinarySearchTree.h"

using namespace std;

// 이진 탐색 트리


int main()
{
	BinarySearchTree bst;
	bst.Insert(30);
	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(40);
	bst.Insert(50);
	bst.Insert(53);
	bst.Insert(15);
	bst.Insert(36);
	bst.Insert(38);
	bst.Insert(25);

	bst.Delete(30);

	bst.Print();

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << bst.Max()->key << endl;
	cout << bst.Min()->key << endl;
	cout << bst.Next()->key << endl;

	return 0;
}