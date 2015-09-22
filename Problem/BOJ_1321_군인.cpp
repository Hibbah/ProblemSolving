/**********************************************************************************

2015.09.22
https://www.acmicpc.net/problem/1321

- title : ����
- input : �׷��� �� N(<=500,000), N���� �� �׷��� �ʱ� �ο�(<=1,000), ������ �� M(<=10,000),
- query : M���� ���Ǹ��� �Ʒ��� ������ �����ϰų� �䱸�ϴ� ���� ���
	- [1 b c] :: b�� �׷쿡 |c|���� �߰��ǰų� ��������
	- [2 b] :: b��° ����� �Ҽӵ� �׷��� ��ȣ�� ���
- issue :
	1. �� �׷��� �ο��� ���������� ��ȭ�ϴ� ��Ȳ.
	2. 1��~X�� �׷������ �ο��� ������ �κ��� SUM(1, X)��� �� ��, 
	   SUM(1, X) >= B �� �����ϴ� �׷� ��ȣ X�� ��� ���� ã�� ���ΰ�
- solution : 
	1. Ư�� ������ ���� ������ ����� �� �ִ� SegmentTree(FenwickTree)���� ����
	2. SUM(1, X) >= B �� �����ϴ� X�� parametric search�� Ž��

- complexity : O( NlogN + M(logN)^2 )
	1. FenwickTree ���� �ð� NlogN
	2. �α� ��ȭ ���� ó���ð� logN, B��° ����� ���� �׷��� ��ȣ ��� �ð� (logN)^2

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// FenwickTree
class Fenwick
{
public:
	int tree[500002];
	int n;

	Fenwick() {}
	Fenwick(const int size)
	{
		n = size + 1;
		memset(tree, 0, 4 * n);
	}

	void add(int idx, const int & val)
	{
		++idx;
		while (idx < n)
		{
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}

	int sum(int idx)
	{
		++idx;
		int ret = 0;
		while (idx > 0)
		{
			ret += tree[idx];
			idx -= (idx & -idx);
		}
		return ret;
	}
};

int n, m;

// parametric search
// return the first index 'idx' satisfying [ SUM(arr[1]~arr[idx]) >= sum ]
int getGroupNum(Fenwick & fenwick, const int & sum)
{
	int l = 1, r = n; // index
	int ret = n;

	while (l <= r)
	{
		const int mid = (l + r) / 2;
		if (fenwick.sum(mid) >= sum)
		{
			r = mid - 1;
			ret = min(ret, mid);
		}
		else l = mid + 1;
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	// input
	scanf("%d", &n);
	Fenwick fenwick(n + 1); // create FenwickTree
	for (int i = 1; i <= n; ++i)
	{
		int num; scanf("%d", &num);
		fenwick.add(i, num);
	}

	// query
	scanf("%d", &m);
	while (m--)
	{
		int a, b, val;
		scanf("%d", &a); // operation type

		switch (a)
		{
		case 1: // arr[b] += val
			scanf("%d %d", &b, &val);
			fenwick.add(b, val);
			break;

		case 2: // print the group number that include 'b'
			scanf("%d", &b);
			printf("%d\n", getGroupNum(fenwick, b));
			break;
		}
	}
	return 0;
}
