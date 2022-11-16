
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

// 이진 탐색 트리



// 이진 탐색 (binary search)
// 

vector<int> numbers;

void BinarySearch(int N)
{
	int right = (int)numbers.size() - 1;
	int left = 0;

	int cost = 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (N < numbers[mid])
		{
			right = mid - 1;
			cost++;
		}
		else if (N > numbers[mid])
		{
			left = mid + 1;
			cost++;
		}
		else
		{
			cout << cost << "번 만에 찾음" << endl;
			return;
		}
	}

	cout << "존재 하지 않음" << endl;
}

int main()
{
	numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81, 91, 100, 102, 103, 105, 106, 109};
	BinarySearch(1);

	return 0;
}