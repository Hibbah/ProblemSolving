/********************************************************************************************

2015.11.07
http://codeforces.com/contest/592/problem/D

- title : Super M
- input : N(<=123456)���� ��带 ������ Ʈ��, M(<=N)���� ���� ���� ��ȣ
- output : ��� ���͸����� �湮�ϴ� �Ÿ��� �ּҷ� �ϱ� ���� ���������� �ּ��̵��Ÿ�
- solution : ������ ���̸� �̵��ϴ� ��λ� �����ϴ� ��� ������ �� - Ʈ���� ����
- complexity : O(N)

********************************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef vector <int> VI;
typedef vector <VI> VVI;

int n, m, maxlen;
bool isMonster[123457];
bool visit[123457];
VVI adj; // adjacent list

// here�� ��Ʈ���ϴ� ����Ʈ������ �������� �̸��� ��λ� �ִ� ��� ������ �� ��ȯ
int DFS(const int & here, const int len, int & END)
{
	visit[here] = true; // visit check

	// Ʈ���� ���� ���
	if (isMonster[here] && len >= maxlen)
	{
		if (len > maxlen) END = here;
		else END = min(END, here); // len == maxlen
		maxlen = len;
	}

	// �������� ���� ��λ� �ִ� ������ ��
	int nearMonsterCnt = 0;
	for (int i = 0; i < adj[here].size(); ++i)
	{
		const int & there = adj[here][i];
		if (visit[there]) continue;
		nearMonsterCnt += DFS(there, len+1, END);
	}
	if (nearMonsterCnt > 0 || isMonster[here]) ++nearMonsterCnt;

	return nearMonsterCnt;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &n, &m);

	// construct Tree (acyclic Graph)
	adj = VVI(n+1);
	for (int i = 1; i < n; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	for (int i = 0; i < m; ++i)
	{
		int monster;
		scanf("%d", &monster);
		isMonster[monster] = true;
	}
	
	// Ʈ���� ������ �����ϴ� �糡��
	int start = 999999, end = 999999;

	maxlen = 0;
	DFS(1, 0, start);

	memset(visit, false, sizeof(visit));
	maxlen = 0; // Ʈ���� ���� ����
	int edgeCnt = DFS(start, 0, end) - 1; // ������-1 == �������� �̸��� ��λ��� ������ ����
	printf("%d\n%d\n", min(start, end), edgeCnt*2 - maxlen);

	return 0;
}