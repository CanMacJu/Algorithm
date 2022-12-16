
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>
#include "BinarySearchTree.h"
#include <thread>
#include <windows.h>

using namespace std;


__int64 cache[50][50];

__int64 combination(int n, int r)
{
	if (n == r || r == 0)
	{
		return 1;
	}

	__int64& ret = cache[n][r];
	if (ret != -1)
	{
		return ret;
	}

	return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}

int main()
{
	::memset(cache, -1, sizeof(cache));

	__int64 start = GetTickCount64();

	long long lotto = combination(45, 15);

	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;

	cout << lotto << endl;


	return 0;
}