
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

// 해시 테이블

// Q map vs hash_map (C++11 표준 unordered_map)

// map: Red-Black Tree
// - 추가/탐색/삭제 O(logN)
// 
// 
// C# dictionary = C++ map (X)
// C# dictionary = C++ unordered_map
// 
// 
// hash_map(unordered_map)
// - 추가/탐색/삭제 O(1)
//
// -> 메모리를 내주고 속도를 취한다

// 해시
// 테이블


void TestTable()
{
	struct User
	{
		int userId = 0;	// 1 - 999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	users[777] = User{ 777,"KimSsenChar" };

	string userName = users[777].username;
	cout << userName << endl;
}


// 보안
// 
// 
// 
//
void TestHash()
{
	struct User
	{
		int userId = 0;	// 1 - int32_MAX
		string username;
	};

	vector<User> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId & 1000);
	users[key] = User{ userId, "CanMacJu" };

	User& user = users[key];
	if (user.userId == userId)
	{
		string name = users[key].username;
		cout << name << endl;
	}

	// 충동 문제
	// 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아 나서면 된다
	// - 선형 조사법 (linear probing)
	// - 이차 조사법 (quadratic probing)

}

void TestHashTableChaining()
{
	struct User
	{
		int userId = 0;	// 1 - int32_MAX
		string username;
	};

	vector<vector<User>> users;
	users.resize(1000);

	const int userId1 = 123456789;
	int key = (userId1 % 1000);
	users[key].push_back(User{ userId1, "CanMacJu" });

	const int userId2 = 789;
	key = (userId2 % 1000);
	users[key].push_back(User{ userId2, "KimSsenChar" });

	vector<User>& bucket = users[key];
	for (User& user : bucket)
	{
		if (user.userId == userId1)
		{
			string name = user.username;
			cout << name << endl;
		}
	}
		
	for (User& user : bucket)
	{
		if (user.userId == userId2)
		{
			string name = user.username;
			cout << name << endl;
		}
	}

	
}



int main()
{
	//TestTable();
	//TestHash();
	TestHashTableChaining();

	return 0;
}