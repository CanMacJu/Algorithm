
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() {}
	Node(const string& data) : data(data) {}

	string data;

	vector<NodeRef> children;
};

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class priority_Queue
{
public:

	void push(const T& data)
	{
		int now = static_cast<int>(_heap.size());
		_heap.push_back(data);

		while (now != 0)
		{
			int parent = (now - 1) / 2;
			if (_predicate(_heap[now], _heap[parent]))
			{
				break;
			}

			std::swap(_heap[parent], _heap[now]);
			now = parent;
		}
	}

	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;
		while (true)
		{
			int next = now;

			int left = (now * 2) + 1;
			if (left >= _heap.size())
			{
				break;
			}

			// 왼쪽 값과 비교
			if (_predicate(_heap[now], _heap[left]))
			{
				next = left;
			}

			// 위 비교 중 큰 수와 오른쪽 비교
			int right = (now * 2) + 2;
			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
			{
				next = right;
			}

			if (now == next)
			{
				break;
			}

			std::swap(_heap[next], _heap[now]);
			now = next;
		}
	}


	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

	int size()
	{
		return static_cast<int>(_heap.size());
	}

private:
	Container _heap = {};
	Predicate _predicate = {};

};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
	}

	return root;
}

void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		cout << "--";
	}
	cout << root->data << endl;

	for (auto child : root->children)
	{
		PrintTree(child, depth + 1);
	}
}

int GetHeight(NodeRef root)
{
	int Height = 1;
	for (auto child : root->children)
	{
		if (Height < GetHeight(child) + 1)
		{
			Height = GetHeight(child) + 1;
		}

		//Height = max(Height, GetHeight(child) + 1);
	}

	return Height;
}




int main()
{
	auto pQ = priority_Queue<int, vector<int>, less<int>>();
	pQ.push(3);
	pQ.push(5);
	pQ.push(10);
	pQ.push(50);
	pQ.push(2);
	pQ.push(100);
	pQ.push(90);
	pQ.push(11);
	pQ.push(1);
	pQ.push(15);


	cout << "Size: " << pQ.size() << endl;

	while (pQ.empty() == false)
	{
		int value = pQ.top();
		pQ.pop();

		cout << "Value: " << value << endl;
	}

	return 0;
}