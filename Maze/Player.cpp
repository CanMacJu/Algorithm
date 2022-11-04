#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
	
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

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

	Pos front[DIR_COUNT] = { Pos{-1, 0}, Pos{0, -1}, Pos{1, 0}, Pos{0, 1} };
	Pos right[DIR_COUNT] = { Pos{0, 1}, Pos{-1, 0}, Pos{0, -1}, Pos{1, 0} };

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
				_dir = (_dir + 1) % DIR_COUNT;
			}
		}
		else
		{
			pos = pos + right[_dir];
			_path.push_back(pos);
			_dir = (_dir + DIR_COUNT - 1) % DIR_COUNT;
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

	Pos front[DIR_COUNT] = { Pos{-1, 0}, Pos{0, -1}, Pos{1, 0}, Pos{0, 1} };
	Pos right[DIR_COUNT] = { Pos{0, 1}, Pos{-1, 0}, Pos{0, -1}, Pos{1, 0} };

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

	/*while (parent[pos] != pos)
	{
		_pathStack.push(pos);
		pos = parent[pos];
	}
	_pathStack.push(pos);*/

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
