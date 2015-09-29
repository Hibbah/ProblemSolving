/**********************************************************************************

2015.09.29
http://codeforces.com/problemset/problem/577/B

- title : Modulo Sum
- input : N(<=1,000,000), M(<=1,000), arr[N](<= 1,000,000,000)
- output : arr�� �κ����� ��, ���� M���� ���� ����� 0�� �Ǵ� �κ������� �����ϴ°�?
- issue :
	1. �κ������� �� == 2^N
	2. dp[idx][R] : idx~ �� �������� M���� ���� ����� R�� �Ǵ� �κ������� ����
		=> dp[N][M] == 1,000,000,000 => �޸�&�ð� �ʰ�

- solution :
	Sum[a][b] : arr[a]~arr[b]������ ���������� ����.
	N > M�� ���, ��ѱ����ǿ����� ���� Sum[0][i]%M == Sum[0][j]%M�� ���� �ٸ� i,j���� �ݵ�� ����.
	i < j, Sum[0][i]%M == Sum[0][j]%M == R �̶�� ���� �ϸ�,
	Sum[0][j] = Sum[0][i] + Sum[i+1][j]����
	Sum[0][j] % M = ( Sum[0][i]%M + Sum[i+1][j]%M ) % M �� �ǰ�,
	R == ( R + Sum[i+1][j]%M ) % M �̹Ƿ�, �ݵ�� Sum[i+1][j]%M == 0�� �����ؾ���.
	����, ���� M���� ���� ����� 0�� �Ǵ� �κ����� Set[i+1][j]�� �ݵ�� ������.

	1. N > M�� ���, ������ "YES"�� ���
	2. N <= M�� ���, dp[1000][1000] ���� ����

- complexity : O(M^2)

**********************************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned long long ull;

int n, m;
int arr[1000001];
ull dp[1001][1001];

// arr[idx]~arr[n-1]�� ������, ���� M���� ���� ����� R�� �κ������� ���� ��ȯ
ull isPossible(const int idx, const int R)
{
	if (idx == n) return R == 0 ? 1 : 0;

	ull & ret = dp[idx][R]; // memoization
	if (ret != -1) return ret;
	ret = 0;

	ret = isPossible(idx + 1, R); // arr[idx]�� �������� ���� ���
	ret += isPossible(idx + 1, (R + m - arr[idx]) % m); // arr[idx]�� �����ϴ� ���

	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
		arr[i] %= m;
	}
	bool result;
	if (n > m) result = true;
	else result = isPossible(0, 0) >= 2 ? true : false;
	// �ƹ��͵� �������� ���� �κ�����(������)�� �����Ͽ�, �����ϴ� �κ������� 2�� �̻��� ��츸 true
	
	printf("%s\n", result ? "YES" : "NO");

	return 0;
}

