
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>

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
vector<bool> visited;
vector<int> cost;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

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
		{ -1, 15, -1, 35, -1, -1 },
		{ 15, -1, +5, 10, -1, -1 },
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, +5, -1 },
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, +5, -1 }
	};

	/*adjacent = vector<vector<int>>
	{
		{ -1, 35, -1, 15, -1, -1 },
		{ -1, -1, -1, -1, +7, -1 },
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, 10, +8, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, +5, -1 },
	};*/
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


// 다익스트라 알고리즘
void Dijkstra(int here)
{
	vector<int> parent(6, -1);

	queue<int> q;
	q.push(here);
	parent[here] = here;
	cost[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();
		visited[here] = true;

		map<int, int> m;
		m.clear();
		for (int there = 0; there < adjacent[here].size(); ++there)
		{
			if (adjacent[here][there] == -1)
			{
				continue;
			}

			if (visited[there])
			{
				continue;
			}

			m.insert({ adjacent[here][there], there });

			parent[there] = here;
			int newCost = cost[here] + adjacent[here][there];
			if (newCost < cost[there])
			{
				cost[there] = newCost;
			}
		}

		for (auto iter = m.begin(); iter != m.end(); ++iter)
		{
			q.push(iter->second);
		}

		/*for (auto iter : m)
		{
			int Index = iter.second;
			q.push(Index);
		}*/
		
	}

	for (int i = 0; i < cost.size(); ++i)
	{
		if (cost[i] == INT_MAX)
		{
			continue;
		}

		cout << "Index: " << i << endl;
		cout << "Cost: " << cost[i] << endl;
		cout << endl;
	}
}

void Dijkstra2(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	// 발견 목록
	list<VertexCost> discovered;
	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost{here, 0});
	best[here] = 0;
	parent[here] = 0;

	while (discovered.empty() == false)
	{
		// 제일 좋은 후보를 찾음
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto iter = discovered.begin(); iter != discovered.end(); ++iter)
		{
			const int cost = iter->cost;

			if (cost < bestCost)
			{
				bestCost = cost;
				bestIt = iter;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);


		if (best[here] < cost)
		{
			continue;
		}

		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == -1)
			{
				continue;
			}

			int nextCost = best[here] + adjacent[here][there];
			if (best[there] < nextCost)
			{
				continue;
			}

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}

	}

	for (int i = 0; i < best.size(); ++i)
	{
		if (best[i] == INT32_MAX)
		{
			continue;
		}

		cout << "Vertex: " << i << endl;
		cout << "  Cost: " << best[i] << endl;
		cout << "Parent: " << parent[i] << endl;
		cout << endl;
	}

}


int main()
{
	CreateGraph();

	discovered = vector<bool>(6, false);
	visited = vector<bool>(6, false);
	cost = vector<int>(6, INT_MAX);

	Dijkstra2(0);

	return 0;
}