
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>
#include "BinarySearchTree.h"
#include <thread>

using namespace std;

// 이진 탐색 트리


int main()
{
	BinarySearchTree bst;
	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(40);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(50);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(41);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(42);
	bst.Print();
	this_thread::sleep_for(1s);

	return 0;
}