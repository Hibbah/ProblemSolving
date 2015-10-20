/*************************************************************************************

2015.10.20
https://www.acmicpc.net/problem/1162
(USA Computing Olympiad 2009 Gold - problem3)

- input : undirected graph G<V, E>(V<=10,000. E<=50,000). K(<=20)
- output : �ִ� K���� ���� ����ġ�� 0���� ����� �۾��� �����Ͽ�, 1��~N�� ������ �̸��� �ִܰŸ�
- solution : Dijkstra�˰��� ����
	1. ���� �� �ϳ��� ����(���������� �������� �̸��� �ִܰŸ�==0)�κ���
	   �ִܰŸ� ������ ���������� Ȯ���Ű�鼭 ��� �ִܰ�θ� ����ϴ� Dijkstra�� ������ �̿�
	2. dist[U][cnt] == cnt���� ������ �����Ͽ� U�� �����Ͽ��� ���� �ִܰŸ��� ����.
	   ����, ��ȭ���� dist[V][cnt] == min( dist[U][cnt] + E(U,V), dist[U][cnt-1] ).

- complexity : O( Elog(KV) )

*************************************************************************************/

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;
typedef vector<vector<PI>> ADJ;

#define COST first.cost
#define CNT first.cnt
#define VTX second

const int INF = 999999999;
int n, m, k;
ADJ adj; // adjacent list

class Entry
{
public:
	int cost, cnt;

	Entry() {}
	Entry(const int & _cost, const int & _cnt) : cost(_cost), cnt(_cnt) {}

	bool operator < (const Entry & e) const
	{
		if (cost != e.cost) return cost < e.cost;
		return cnt < e.cnt;
	}
}; typedef pair<Entry, int> ITEM;

VVI Dijkstra()
{
	VVI dist(n + 1, VI(k+1, INF)); // dist[V][k] : k���� ������ �����Ͽ� V�� �̸��� �ִܰŸ�
	for (int cnt = 0; cnt <= k; ++cnt) dist[1][cnt] = 0; // ���������� �������� �̸��� �Ÿ��� 0
	priority_queue <ITEM, vector<ITEM>, greater<ITEM>> pq; // minhaep
	pq.push({ Entry(0, 0), 1 });

	while (pq.size())
	{
		const int here = pq.top().VTX;
		const int cost = pq.top().COST;
		const int cnt = pq.top().CNT;
		pq.pop();

		for (int i = 0; i < adj[here].size(); ++i)
		{
			const int & there = adj[here][i].first;
			const int newcost = adj[here][i].second + cost;

			if (newcost < dist[there][cnt]) // �����ϴ� ���� ���
			{
				dist[there][cnt] = newcost;
				pq.push({ Entry(newcost, cnt), there });
			}
			if (cnt < k && cost < dist[there][cnt + 1]) // ������ �����ϴ� ���
			{
				dist[there][cnt+1] = cost;
				pq.push({ Entry(cost, cnt+1), there });
			}
		}
	}
	return dist;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %d", &n, &m, &k);

	adj = ADJ(n+1); // adjacent list
	
	// construct graph
	while (m--)
	{
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		adj[a].push_back({b, w});
		adj[b].push_back({a, w});
	}

	VVI && dist = Dijkstra();
	printf("%d\n", *min_element(dist[n].begin(), dist[n].end()));

	return 0;
}
