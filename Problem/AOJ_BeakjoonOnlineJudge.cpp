/**********************************************************************************

2015.09.02
https://algospot.com/judge/problem/read/BOJ
https://www.acmicpc.net/problem/1261

- title : Beacjoon Online Judge (�˰���)
- input : H, W (<= 100). H*W ũ���� ���̺�.
- output : <1, 1>���� <H, W>�� �̸��� ���� �ν����ϴ� �ּ� ��('1')�� ����
- solution :
	1. minCnt[y][x] : <1, 1>���� <x, y>�� �̸������� �ν����ϴ� �ּ� ���� ����
	2. ���ʿ� �־��� �� �ϳ��� ���� minCnt[1][1] = 0 ���κ��� minCnt[H][W]���� Ȯ��
	3. ��ȭ�� : minCnt[y][x] == min( minCnt[Y][X] ) + (<x, y>==�� ? 1 : 0).
				<X, Y>�� <x, y>�� ������ �� ����
	4. ���� ������ ��ġ���� ���������� Ž���ϱ� ���� ���� �μ� ���� ������ ���� ���� ��ġ���� Ž��
		(�ڷᱸ�� minheap. STL::priority_queue �̿�)

- complexity : HW*log(HW)

***********************************************************************************/


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef vector <string> VS;
typedef vector <int> VI;
typedef vector <VI> VVI;

int h, w;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
VS table;

class Item
{
public:
	int x, y, cnt;

	Item(const int & _x, const int & _y, const int _cnt) : x(_x), y(_y), cnt(_cnt) {}
	bool operator > (const Item & p) const
	{
		return cnt > p.cnt;
	}
};

// Priority(distance) First Search
int PFS()
{
	bool visit[101][101] = { true, };
	priority_queue <Item, vector <Item>, greater <Item> > pq; // minheap <dist, <x, y>>
	pq.push(Item(0, 0, 0));

	while (pq.size())
	{
		const int x = pq.top().x;
		const int y = pq.top().y;
		const int dist = pq.top().cnt;
		pq.pop();

		for (int d = 0; d < 4; ++d)
		{
			const int X = x + dx[d];
			const int Y = y + dy[d];
			if (!(0 <= X&&X < w && 0 <= Y&&Y < h) || visit[Y][X]) continue;
			if (X == w - 1 && Y == h - 1) return dist;
			visit[Y][X] = true;
			pq.push(Item(X, Y, table[Y][X] == '0' ? dist : dist + 1));
		}
	}
	return 0;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &w, &h);
	table = VS(h);
	for (int i = 0; i < h; ++i) cin >> table[i];
	printf("%d\n", PFS());

	return 0;
}