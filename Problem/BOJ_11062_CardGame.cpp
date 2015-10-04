/**********************************************************************************

2015.10.04
https://www.acmicpc.net/problem/11062
(ACMICPC Asia Regional - Daejeon Internet Competition 2015 problem B)

- title : Card Game
- input : ī���� ���� N(<=1,000), N���� ī�尪(1~10,000)
- output :
	�������� ��ǻ�Ͱ� �� �Ͼ� �����ư��鼭 �� ���� �Ǵ� �� ������ ī�带 �������� ������ �Ѵ�.
	������ ���������� �����ϸ�, ��ǻ�ʹ� �� ���� �������� �����Ϸ��� �ּ��� ���Ѵٰ� ���� ��,
	��������� �������� ���� �� �ִ� ������ �ִ밪�� ���.

- solution :
	1. maxScore(l, r) : ���� l~r���� �������� ���� �� �ִ� ������ �ִ밪 ��ȯ
	2. �������� card[l]�� �������� ���, ��ǻ�Ϳ��� �־����� ������ [l+1 ~ r].
	3. ��ǻ���� ���� ���� �ٽ� �������� �Ͽ��� ���� �� �ִ� ������ [l+2 ~ r]�Ǵ� [l+1 ~ r-1].
	4. ��ǻ�ʹ� �������� [l+2 ~ r]�� [l+1 ~ r-1]�߿� �ּҰ��� ���� �� ��츦 ���� ��.
	5. ����, ��ȭ����
		maxScore(l, r) = max(
		card[l] + min( maxScore(l+2, r), maxScore(l+1, r-1) ),
		card[r] + min( maxScore(l+1, r-1), maxScore(l, r-2) ) )
	6. ��� �������� ������ �Է� ������ ���� �ߺ������� ������ �� �����Ƿ� dp�� ����
	
- complexity : O(N^2)

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int arr[1010];
int cache[1010][1010];

// return the maximum Score in range(l ~ r)
int maxScore(const int l, const int r)
{
	if(r < l) return 0; // invalid range
	if(l == r) return arr[l]; // base case

	int & ret = cache[l][r]; // memoization
	if(ret != -1) return ret;
	ret = 0;

	// recursive
	ret = max(ret, arr[l] + min(maxScore(l+2, r), maxScore(l+1, r-1)));
	ret = max(ret, arr[r] + min(maxScore(l+1, r-1), maxScore(l, r-2)));

	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	int t;
	scanf("%d", &t);
	while(t--)
	{
		memset(cache, -1, sizeof(cache)); // initialize memoization table 
		int n; scanf("%d", &n);
		for(int i=0; i<n; ++i) scanf("%d", &arr[i]); // card values
		printf("%d\n", maxScore(0, n-1));
	}
	return 0;
}