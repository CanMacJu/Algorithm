
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

// 1) 버블 정렬 -> 시간 복잡도 O(N^2)
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (v[j] > v[j + 1])
			{
				std::swap(v[j], v[j + 1]);
			}
		}
	}
}

// 2) 선택 정렬
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; ++i)
	{
		int bestIndex = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (v[j] < v[bestIndex])
			{
				bestIndex = j;
			}
		}

		std::swap(v[i], v[bestIndex]);
	}
}


// 3) 삽입 정렬

void InsertionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 1; i < n; ++i)
	{
		int insertData = v[i];

		int j;
		for (j = i - 1; j >= 0; --j)
		{
			if (v[j] > insertData)
			{
				v[j + 1] = v[j];
			}
			else
			{
				break;
			}
		}

		v[j + 1] = insertData;
	}
}
 


int main()
{
	vector<int> v = { 5, 3, 10, 1, 9 };

	for (auto n : v)
	{
		cout << n << ", ";
	}
	cout << endl;

	//BubbleSort(v);
	//SelectionSort(v);
	InsertionSort(v);
	for (auto n : v)
	{
		cout << n << ", ";
	}
	cout << endl;

	return 0;
}