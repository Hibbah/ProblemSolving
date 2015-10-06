/*************************************************************************************

2015.10.06
https://www.acmicpc.net/problem/11066
(ACMICPC Asia Regional - Daejeon Internet Competition 2015 problem B)

- title : Merging Files
- input : N(<=500), N integers(<=10,000)
- output :
	'������' �� ���� �ϳ��� ��ġ�µ� �ʿ��� ����� �� ���� ���� ��,
	�־��� N���� ���ڵ��� �ϳ��� ��ġ�µ� �ʿ��� �ּҺ���� ���.

- issue :
	greedy����(�� ���� ������ �� ���� ���� �ּ��� ���� ��ħ)���δ� �Ұ���.
	���� �ܰ迡�� �ּ��� ������ ���� �ܰ迡�� ���� ���� ����� ������ �� ����.
	=> �ٸ� ���� �ְų�, ��� ��츦 �� �����غ��� ��.

- solution :
	1. ���� N���� �־����� ��, �׻� N-1���� ��ġ�� ������ ����. (����� �ٸ���, ��ġ�� Ƚ���� ����)
	2. ���� [l, r]�� ����, ��ġ�� ����� �پ������� ��ģ ������� Sum[l, r]�� ����.
	3. minCost[l, r] == ���� [l, r]�� ���ڵ��� �ϳ��� ��ġ�µ� �ʿ��� �ּҺ������ ����.
	4. minCost[l, r]= min( minCost[l, k] + minCost[k+1, r] + Sum[l, r] ). (l<=k<r)
	=> �־��� ����[l, r]�� ����, l<=k<r�� �����ϴ� k�� �������� [l, k], [l+1, r]�� �켱������ ��ġ��
	   �� ����� ���� �� ���ڸ� ���������� ���ļ� �ϳ��� ���ڷ� ���鶧 �ʿ��� �ּҺ��
	   ���������� ���� �� ���ڸ� ��ġ�µ� �ʿ��� ��� = Sum[l, l] + Sum[l+1, r] = Sum[l, r]
	5. ���ڸ� �ϳ��� ��ġ�µ� ������ ��� ��츦 ���.
	   ��� �������� ������ ����[l, r]�� ���� �ּҺ���� ����� �ߺ����� ������ �� �����Ƿ� DP��ũ�� �̿�

- complexity : O(N^3)

*************************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 999999999999;
ll card[502]; // data
ll Sum[502]; // Sum[a] == Sum(card[0] ~ card[a])
ll cache[502][502]; // memoization table

// return the minimum Cost to combine a number one
ll minCost(const int l, const int r)
{
    if (l == r) return 0;
    if (l + 1 == r) return card[l] + card[r];
 
    ll & ret = cache[l][r]; // memoization
    if (ret != -1) return ret;
    ret = INF;
 
    for (int mid = l; mid < r; ++mid) // split range [l, mid] + [mid+1, r]
    {
		// minCost[l, r] = min( minCost[l, mid] + minCost[mid+1, r] + Sum(card[l]~card[r]) )
        ret = min(ret, minCost(l, mid) + minCost(mid+1, r) + Sum[r] - Sum[l-1]);
    }
    return ret;
}
 
int main()
{
#ifdef _CONSOLE
    freopen("input.txt", "r", stdin);
#endif
 
    int t;
	scanf("%d", &t);
    while (t--)
    {
        memset(cache, -1, sizeof(cache)); // init the memoization table
        
		// input data
		int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &card[i]);
            Sum[i] = Sum[i - 1] + card[i]; // calc subsum
        }
        
		printf("%lld\n", minCost(1, n));
    }
 
    return 0;
}