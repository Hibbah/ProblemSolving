/****************************************************************************************

2015.10.26
http://codeforces.com/contest/591/problem/C
CF #327 (Div.2) - problem C

- title : Median Smoothing
- input : �ִ� ���� 500,000�� 0/1�θ� ������ �迭 arr[]
- output : arr[]�� stable ���°� �� ������ �ɸ��� �ּ� �ð� & ���� stable���¸� ���. (�Ұ����ϸ� -1)
	1. arr[i]���� ���� �ܰ迡�� �ڱ� �ڽŰ� �� ���� ���ҵ��� �߰������� ��ȭ�ȴ�.
	   (���� ù ��° ���ҿ� ������ ���Ҵ� ó�� �Է¹��� ���� �״�� �����Ѵ�.)
	2. arr[]�� ��� ���Ҹ� ���� ��Ĵ�� �����ϴµ� 1�� �ð��� �ʿ�.
	3. arr[]�� ������ ������. ��, ��� ���Ұ� �� �̻� ������ ������, arr[]�� stable ���¶�� ��.

- issue : stable�� �� �� ���� �� �ܰ踶�� O(n)��ȯ ���� -> TimeLimit

- solution :
	1. arr[i]�� ���� ���� �ܰ迡�� ��ȭ�Ǵ� ���� �� ����. [1 0 1] or [0 1 0]
	2. ���� ��츦 Ȯ����Ѽ� �����غ���, 0/1�� ����� �����ϴ� ����(Alternate Range)���� ��ȭ �߻�.
	3. Alternate Range = R(l, r)����
	   3-1. arr[l]==arr[r]�� ���, ���������� ������ ��� ���� �����ϰ� ��.
	   3-2. arr[l]!=arr[r]�� ���, arr[l]���� arr[r]���� ���� ���ļ� �������� ������.
	4. R(l, r)�� ���°� stable�� �Ǳ� ���� �ʿ��� �ð��� ���� ������ ���ݸ�ŭ�� ��ȯ �۾��� �ʿ�.

- complexity : O(n)

****************************************************************************************/

#include <stdio.h>
#include <algorithm>

using namespace std;

int n;
int arr[500010];

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	// input
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

	int minn = 0, l = -1, r = -1;
	while (l<n && r<n)
	{
		// find Alternate-Range R(l, r)
		for (l = r + 1; l < n - 1; ++l) if (arr[l] != arr[l+1]) break;
		for (r = l + 1; r < n - 1; ++r) if (arr[r] == arr[r+1]) break;
		
		// Range length >= 3
		if (r-l+1 < 3) continue;

		// to stable state
		const int mid = (l+r)/2;
		for (int i = l; i <= r; ++i)
			arr[i] = i <= mid ? arr[l] : arr[r];

		// the time until stable state that Range(l, r) is (RangeLength-1)/2
		minn = max(minn, (r-l)/2);
	}

	printf("%d\n", minn);
	for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
	puts("");

	return 0;
}

