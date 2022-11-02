#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	while (_path.empty() == false)
	{
		_path.clear();
	}
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = board->GetExitPos();

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
}
