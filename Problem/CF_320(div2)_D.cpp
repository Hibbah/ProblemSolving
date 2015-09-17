/*********************************************************************************

2015.09.17
http://codeforces.com/contest/579/problem/D
( Codeforces#320 (div2)_D )

- title : "OR" Game
- input : N(<=200,000), K(<=10), X(<=8)
- output : N���� ���ڵ� ��. ������ ���ڿ� X�� ���ϴ� ������ �ִ� K�� ������ ��,
	��� ���ڵ��� ��ƮOR������ ������� �ִ밡 �Ǵ� ���� ���
- issue :
	1. ��� ����� �� == ������ 0~K�� �ϴ� ����� �� == 1+N^1+N^2+N^3+...+N^K
	2. ������ K�� ��� ����ϴ� ���� �̵��ΰ� ?
	3. N���� ������ ��. � ���ڿ� X�� ���ϴ� ���� �̵��ΰ� ?
- solution :
- �ڸ����� �������� ��(������)�� ���� Ŀ����.
- X>=2 �̹Ƿ�, � ���ڿ� X�� ���� ������ �������� �ڸ����� �����Ѵ�.
- �ڸ����� ���� �������� �����ϸ� bitwiseOR������ ������� Ŀ����.
=> "�ϳ��� ����"�� "����Ƚ�� K�� ��� ���"�Ͽ� ���ϴ°��� �̵��̴�.

1. bitCnt[i] : i�� ��Ʈ�� set(1)�� ������ ������ ����
2. N���� �� ���ڸ��� X^K�� ���� ����� bitCnt[]�� ����Ͽ� OR���� ���
3. 1~2�� ��������� �ִ밪�� ���

- complexity :
	indexTree solution : O(4N+NlogN)
	'yukariko' solution : O(64N)
	editorial solution : O(N)

*********************************************************************************/

// yukariko solution

#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

int n, k;
int bitCnt[64];
ull x, arr[200001];

// counting the num in binary ( d=1 : set // d=-1 : reset )
void add(ull num, const ull & d)
{
	for (int i = 0; i < 64 && num; ++i)
	{
		if (num & 1) bitCnt[i] += d;
		num >>= 1;
	}
}

// return the number converting the bitCnt[] as decimal
ull getNum()
{
	ull ret = 0, exp = 1;
	for (int i = 0; i < 64; ++i)
	{
		ret += (bitCnt[i] > 0 ? exp : 0);
		exp <<= 1;
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %llu", &n, &k, &x);
	for (int i = 0; i < n; ++i)
	{
		scanf("%llu", &arr[i]);
		add(arr[i], 1);
	}

	ull maxx = 0, mul = 1;
	for (int i = 0; i < k; ++i) mul *= x;
	for (int i = 0; i < n; ++i)
	{
		ull target = arr[i] * mul;
		add(arr[i], -1); // reset arr[i]
		add(target, 1); // set arr[i]*mul
		maxx = max(maxx, getNum()); // bitwise OR for N numbers
		add(target, -1); // reset arr[i]*mul
		add(arr[i], 1); // set arr[i]
	}
	printf("%llu\n", maxx);

	return 0;
}

/****** using INDEX - TREE code

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int n, k;
ull x;
vector <ull> vi;

class SEGTREE
{
public:
	int n;
	vector <ull> tree;

	SEGTREE(const vector <ull> & vi)
	{
		n = vi.size();
		tree.resize(4 * n);
		init(vi, 0, n - 1, 1);
	}

	ull init(const vector <ull> & vi, const int left, const int right, const int node)
	{
		if (left == right) return tree[node] = vi[left];
		const int mid = (left + right) / 2;
		return tree[node] = init(vi, left, mid, node * 2) | init(vi, mid + 1, right, node * 2 + 1);
	}

	ull query(const int & a, const int & b)
	{
		return query(a, b, 1, 0, n - 1);
	}
private:
	ull query(const int & a, const int & b, const int node, const int & nodeleft, const int & noderight)
	{
		if (b < nodeleft || noderight < a) return 0;
		if (a <= nodeleft && noderight <= b) return tree[node];
		const int mid = (nodeleft + noderight) / 2;
		return query(a, b, node * 2, nodeleft, mid) | query(a, b, node * 2 + 1, mid + 1, noderight);
	}
};

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %llu", &n, &k, &x);
	vi = vector <ull>(n);
	for (int i = 0; i < n; ++i) scanf("%llu", &vi[i]);

	SEGTREE segtree(vi);
	ull maxx = 0, mul = 1;
	for (int i = 0; i < k; ++i) mul *= x;
	for (int i = 0; i < n; ++i)
	{
		ull target = vi[i] * mul;
		ull left = i == 0 ? 0 : segtree.query(0, i - 1);
		ull right = i == n - 1 ? 0 : segtree.query(i + 1, n - 1);
		maxx = max(maxx, target | left | right);
	}
	printf("%llu\n", maxx);

	return 0;
}

*/


/************** CF :: editorial code

#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

const int SIZE = 2e5;
ull arr[SIZE], pre[SIZE], suf[SIZE];

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	int n, k, x;
	scanf("%d %d %d", &n, &k, &x);
	for (int i = 0; i < n; ++i) scanf("%llu", &arr[i]);

	pre[0] = arr[0]; suf[n - 1] = arr[n - 1];
	for (int i = 1; i < n; ++i) pre[i] = pre[i - 1] | arr[i];
	for (int i = n - 2; i >= 0; --i) suf[i] = suf[i + 1] | arr[i];

	ull mul = 1, maxx = 0;
	while (k--) mul *= x;
	for (int i = 0; i < n; ++i)
		maxx = max(maxx, (arr[i] * mul | pre[i - 1] | suf[i + 1]));

	printf("%llu\n", maxx);

	return 0;
}

*/