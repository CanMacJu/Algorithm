#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	//Bfs();
	AStar();
	
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		//_board->GenerateMap_Kruskal();
		_board->GenerateMap_Prim();
		Init(_board);
		return;
	}

	if (_sumTick >= MOVE_TICK)
	{
		SetPos(_path[_pathIndex]);
		_pathIndex++;

		_sumTick = 0;
	}
	else
	{
		_sumTick += deltaTick;
	} 

	/*if (_pathStack.empty())
		return;

	if (_sumTick >= MOVE_TICK)
	{
		Pos pos = _pathStack.top();
		_pathStack.pop();

		SetPos(pos);

		_sumTick = 0;
	}
	else
	{
		_sumTick += deltaTick;
	}*/
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;

	while (_path.empty() == false)
	{
		_path.clear();
	}
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] = { Pos{-1, 0}, Pos{0, -1}, Pos{1, 0}, Pos{0, 1} };
	Pos right[4] = { Pos{0, 1}, Pos{-1, 0}, Pos{0, -1}, Pos{1, 0} };

	while (pos != dest)
	{
		if (_board->GetTileType(pos + right[_dir]) == TileType::WALL)
		{
			if (_board->GetTileType(pos + front[_dir]) == TileType::EMPTY)
			{
				pos = pos + front[_dir];
				_path.push_back(pos);
			}
			else
			{
				_dir = (_dir + 1) % 4;
			}
		}
		else
		{
			pos = pos + right[_dir];
			_path.push_back(pos);
			_dir = (_dir + 4 - 1) % 4;
		}
	}

	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; ++i)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	if (_path.empty() == false)
	{
		s.push(_path.back());
	}

	vector<Pos> q;
	while (s.empty() == false)
	{
		q.push_back(s.top());
		s.pop();
	}

	std::reverse(q.begin(), q.end());

	_path = q;
}

void Player::Bfs()
{
	Pos pos = _pos;

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] = { Pos{-1, 0}, Pos{0, -1}, Pos{1, 0}, Pos{0, 1} };
	Pos right[4] = { Pos{0, 1}, Pos{-1, 0}, Pos{0, -1}, Pos{1, 0} };

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	map<Pos, Pos> parent;

	queue<Pos> q;

	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// 방문
		if (pos == dest)
		{
			break;
		}

		for (int32 dir = 0; dir < 4; ++dir)
		{
			Pos nextPos = pos + front[dir];
			if (discovered[nextPos.y][nextPos.x])
			{
				continue;
			}
			if (CanGo(nextPos) == false)
			{
				continue;
			}

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}

	}

	_path.clear();

	pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (parent[pos] == pos)
		{
			break;
		}

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());


}

struct PQNode
{

	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int32 f;	// f = g + h
	int32 g;
	Pos pos;
};



void Player::AStar()
{
	// 점수 매기기
	// F = G + H
	// F = 최종 점수( 작을 수록 좋음, 경로에 따라 달라짐 )
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용( 작을 수록 좋음, 경로에 따라 달라짐 )
	// H =  목적지에서 얼마나 가까운지 ( 작을 수록 좋음, 고정 )


	Pos start = _pos;
	Pos dest = _board->GetExitPos();

	enum
	{
		DIR_COUNT = 4
	};

	Pos front[] = 
	{ 
		Pos{-1, 0}, 
		Pos{0, -1}, 
		Pos{1, 0}, 
		Pos{0, 1}, 
		Pos{-1, -1}, 
		Pos{1, -1}, 
		Pos{1, 1}, 
		Pos{-1, 1} 
	};

	int32 cost[] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	const int32 size = _board->GetSize();

	// ClosedList  방문여부
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용 (작을 수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// 부모 추적 용도
	map<Pos, Pos> parent;

	// OpenList
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) 예약(발견) 시스템 구현
	// 2) 뒤늦게 더 좋은 경로가 발견 될 수 있음 -> 예외 처리 필수

	// 초기값
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		PQNode node = pq.top();
		pq.pop();


		// 선택 1
		if (closed[node.pos.y][node.pos.x])
			continue;
		// 선택 2
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 도착했으면 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];

			if (CanGo(nextPos) == false)
				continue;

			// 선택
			if (closed[nextPos.y][nextPos.x])
				continue;

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			pq.push(PQNode{ g + h, g, nextPos });
			best[nextPos.y][nextPos.x] = g + h;
			parent[nextPos] = node.pos;
		}

	}

	Pos pos = dest;

	_path.clear();
	_pathIndex = 0;

	while (true)
	{
		_path.push_back(pos);

		if (parent[pos] == pos)
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
 