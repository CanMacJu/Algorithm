
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;


// DFS(Depth First Search) 깊이 우선 탐색
// BFS(Breadth First Search) 너비 우선 탑색

struct Vertex
{
	int _data = 4;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// 인접 리스트
	/*adjacent[0].push_back(1);
	adjacent[0].push_back(3);

	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);

	adjacent[3].push_back(4);

	adjacent[5].push_back(4);*/


	// 인접 행렬
	adjacent = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 }
	};
}

// DFS
void Dfs(int here)
{
	// 인접 리스트
	/*visited[here] = true;

	cout << "visited: " << here << endl;

	for (int n : adjacent[here])
	{
		if (visited[n] == false)
			Dfs(n);
	}*/

	// 인접 행렬
	discovered[here] = true;

	cout << "visited: " << here << endl;

	for (auto n : adjacent[here])
	{
		if (n == 0)
		{
			continue;
		}

		if (discovered[n] == false)
		{
			Dfs(n);
		}
	}
}

void DfsAll()
{
	// 인접 리스트
	/*visited = vector<bool>(6, false);

	for (int i = 0; i < vertices.size(); i++)
	{
		if (visited[i] == false)
		{
			Dfs(i);
		}
	}*/


	// 인접 행렬
	discovered = vector<bool>(6, false);

	for (int i = 0; i < discovered.size(); i++)
	{
		if (discovered[i] == false)
		{
			Dfs(i);
		}
	}

}


// BFS
void Bfs(int here)
{
	// 누구에 의해 발견 되었는지?
	vector<int> parent(6, -1);

	// 시작점에서 얼마 만큼 떨어져 있는지?
	vector<int> distance(6, -1);

	// 인접 리스트
	/*queue<int> q;

	q.push(here);
	discovered[here] = true;

	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "visited: " << here << endl;
		cout << "parent: " << parent[here] << endl;
		cout << "distance: " << distance[here] << endl;
		cout << endl;

		for (int there : adjacent[here])
		{
			if (discovered[there])
			{
				continue;
			}

			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}*/


	// 인접 행렬
	queue<int> q;

	q.push(here);
	discovered[here] = true;

	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "visited: " << here << endl;
		cout << "parent: " << parent[here] << endl;
		cout << "distance: " << distance[here] << endl;
		cout << endl;

		for (int there = 0; there < adjacent[here].size(); ++there)
		{
			if (adjacent[here][there] == 0)
			{
				continue;
			}

			if (discovered[there])
			{
				continue;
			}

			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}
}

void BfsAll()
{
	for (int i = 0; i < discovered.size(); ++i)
	{
		if (discovered[i] == false)
		{
			Bfs(i);
		}
	}

}

int main()
{
	CreateGraph();

	discovered = vector<bool>(6, false);

	BfsAll();

	return 0;
}