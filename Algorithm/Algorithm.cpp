
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


// 그래프/트리 응용
// 푀소 스패닝 트리

// 상호 베타적 집합 (Disjoint Set)
// -> 유니온-파인드


// 시간복잡도: 트리의 높이에 비례
class NaiveDisjointSet
{
public:
	NaiveDisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; ++i)
		{
			_parent[i] = i;
		}
	}

	int Find(int u)
	{
		while (_parent[u] != u)
		{
			u = _parent[u];
		}

		return u;



		/*if (u == _parent[u])
		{
			return u;
		}

		return Find(_parent[u]);*/
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		_parent[u] = v;
	}

private:
	vector<int> _parent;

};

// 트리가 한쪽으로 기우는 문제를 해결
// -> 트리를 합칠때, 높이가 낮은 트리를 높이가 높은 트리에 붙임
// -> Union-By-Rank
class DisjointSet1
{
public:
	DisjointSet1(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; ++i)
		{
			_parent[i] = i;
		}
	}

	int Find(int u)
	{
		/*while (_parent[u] != u)
		{
			u = _parent[u];
		}

		return u;*/

		if (u == _parent[u])
		{
			return u;
		}

		return Find(_parent[u]);
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		if (_rank[u] > _rank[v])
		{
			swap(u, v);
			// -> _rank[u] <= _rank[v] 보장
		}

		_parent[u] = v;
		if (_rank[u] == _rank[v])
		{
			_rank[v]++;
		}
	}


private:
	vector<int> _parent;
	vector<int> _rank;

};

class DisjointSet2
{
public:
	DisjointSet2(int n) : _parent(n), _childs(n)
	{
		for (int i = 0; i < n; ++i)
		{
			_parent[i] = i;
		}
	}

	int Find(int u)
	{
		while (_parent[u] != u)
		{
			u = _parent[u];
		}

		return u;

		/*if (u == _parent[u])
		{
			return u;
		}

		return Find(_parent[u]);*/
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		if (Height(u) <= Height(v))
		{
			_parent[u] = v;
			_childs[v].push_back(u);
		}
		else
		{
			_parent[v] = u;
			_childs[u].push_back(v);
		}
	}

	int Height(int u)
	{
		int maxHeight = 0;
		for (int n : _childs[u])
		{
			if (maxHeight < Height(n))
			{
				maxHeight = Height(n);
			}
		}

		return maxHeight + 1;
	}

private:
	vector<int> _parent;
	vector<vector<int>> _childs;

};


int main()
{



	return 0;
}