#pragma once

#include "Types.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>

using namespace std;

struct Pos
{
	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos operator+=(Pos& other)
	{
		y += y + other.y;
		x += x + other.x;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,
	DIR_UP_LEFT = 4,
	DIR_DOWN_LEFT = 5,
	DIR_DOWN_RIGHT = 6,
	DIR_UP_RIGHT = 7,
};