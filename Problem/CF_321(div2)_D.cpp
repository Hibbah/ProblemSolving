/**********************************************************************************

2015.09.23
http://codeforces.com/contest/580/problem/D

- title : Kefa and Dishes
- input : ������ ���� N(<=18), ������ ������ ���� M(<=N), ���� ������ ���� K
N�� ������ ����, K���� ���� ���� ����(A�� B�� �����ؼ� ������ C�� ���� ����)
- output : N�� �߿� ���� �ٸ� M���� ������ ���� ��, �ִ� ������ ���
- issue : ��� ����� �� == (N Combination M)!
- solution :
1. maxScore(prev, cnt, bits)
: ������ prev�� �Ծ��� ������ cnt���� �� �Ծ ���� �� �ִ� �ִ� ���� ��ȯ
(bits == N���� ������ ���� ������ �Ծ���/�ȸԾ��� �� ǥ���� bit-stream)
2. prev���� bits���� ������ ��, maxScore�Լ��� ������ ���� ��ȯ.
��, Ž���������� prev�� bits�� Ư�� ���¸� �����ϰ� ǥ�� ����.
cnt���� bits�� �����Ͽ� ���� �� ������, ������ ���Ǽ��� ���� ���
3. prev(18) * bits(2^18) ũ���� memoizationTable�� �����Ͽ� DP����

- complexity : O( N * 2^N )

**********************************************************************************/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

int n, m, k;
ll score[20];
ll bonus[20][20];
ll cache[19][1 << 18];

// returns the maximum score that can be obtained by eating more 'cnt' foods
ll maxScore(const int & prev, const int cnt, const int state)
{
	if (cnt == 0) return 0;

	ll & ret = cache[prev][state];
	if (ret != -1) return ret;
	ret = 0;

	for (int i = 0; i < n; ++i)
	{
		if (state & (1 << i)) continue; // food 'i' aleady eat
		ret = max(ret, maxScore(i, cnt - 1, state | (1 << i)) + score[i] + bonus[prev][i]);
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	memset(cache, -1, sizeof(cache)); // memoization Table init

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; ++i)
		scanf("%lld", &score[i]);
	while (k--)
	{
		int a, b; ll c;
		scanf("%d %d %lld", &a, &b, &c);
		bonus[a - 1][b - 1] = c;
	}
	printf("%lld\n", maxScore(18, m, 0)); // 18 == garbage value

	return 0;
}
