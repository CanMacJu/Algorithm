
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

// 1) 버블 정렬 O(N^2)
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

// 2) 선택 정렬 O(N^2)
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

// 3) 삽입 정렬 O(N^2)
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
 
// 4) 힙 정렬 O(NlogN)
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	//O(NlogN)
	for (int n : v)
	{
		pq.push(n);
	}

	v.clear();

	// O(NlogN)
	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

// 5) 병합 정렬 
// 분할 정복 (Divide and Conquer)
// - 분할
// - 정복
// - 결합

vector<int> Merge(vector<int> a, vector<int> b)
{
	vector<int> temp;

	int aIndex = 0;
	int bIndex = 0;

	while (aIndex < a.size() && bIndex < b.size())
	{
		if (a[aIndex] <= b[bIndex])
		{
			temp.push_back(a[aIndex]);
			aIndex++;
		}
		else
		{
			temp.push_back(b[bIndex]);
			bIndex++;
		}
	}

	if (bIndex < b.size())
	{
		while (bIndex < b.size())
		{
			temp.push_back(b[bIndex]);
			bIndex++;
		}
	}
	else
	{
		while (aIndex < a.size())
		{
			temp.push_back(a[aIndex]);
			aIndex++;
		}
	}

	return temp;
}

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIndex = left;
	int rightIndex = mid + 1;
	vector<int> temp;

	while (leftIndex <= mid && rightIndex <= right)
	{
		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	for (int i = 0; i < temp.size(); ++i)
	{
		v[i + left] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

// 6) 퀵 정렬

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	// O(N)
	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
		{
			++low;
		}

		while (high >= left + 1 && pivot <= v[high])
		{
			--high;
		}

		if (low < high)
		{
			std::swap(v[low], v[high]);
		}
	}

	std::swap(v[left], v[high]);

	return high;
}

void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
	{
		return;
	}

	int pivot = Partition(v, left, right);

	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}



int main()
{
	vector<int> v;

	srand(time(0));

	for (int i = 0; i < 30; ++i)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}

	//BubbleSort(v);
	//SelectionSort(v);
	//InsertionSort(v);
	//HeapSort(v);
	//MergeSort(v, 0, v.size() - 1);
	QuickSort(v, 0, v.size() - 1);

	for (auto n : v)
	{
		cout << n << ", ";
	}

	return 0;
}