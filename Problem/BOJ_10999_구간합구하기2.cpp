/**************************************************************************************

2015.11.04
https://www.acmicpc.net/problem/10999

- title : ���� �� ���ϱ�2
- input : ���� N(<=1,000,000)�� ������ �����ϴ� �迭. M(<=10,000)���� ����
- ouput :
	1. ���� [a, b]�� ���ԵǴ� ��� ���ҿ� ���� D��ŭ ���Ѵ�. (D�� ������ ����)
	2. ���� [a, b]�� ���ԵǴ� ��� ������ ���� ����Ѵ�.

- issue : �迭�� �����ϴ� Ư�� �� �ϳ��� �����ϴ� ���� �ƴ�, ���� ���� ��� ���� ����
- solution : SegmentTree + lazyPropagation
- complexity :
	1. ����Ʈ�� ���� : O( 4N )
	2. ������/����������Ʈ ���� : O( logN )
	=> total : O( 4N + MlogN )

**************************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector <ll> VI;

class SEGTREE
{
public:
	int n;
	VI tree;
	VI lazy;

	SEGTREE(){}
	SEGTREE(const VI & vi)
	{
		n = vi.size();
		tree = VI(4*n, 0);
		lazy = VI(4*n, 0);
		init(1, 0, n-1, vi);
	}

	ll query(const int a, const int b)
	{
		return query(1, 0, n-1, a, b);
	}

	void update(const int a, const int b, const ll & d)
	{
		update(1, 0, n-1, a, b, d);
	}

private:
	ll init(const int node, const int l, const int r, const VI & vi)
	{
		if (l == r) return tree[node] = vi[l];
		const int mid = (l+r)/2;
		return tree[node] = init(node*2, l, mid, vi) + init(node*2+1, mid+1, r, vi);
	}

	ll query(const int node, const int l, const int r, const int & a, const int & b)
	{
		if (lazy[node] != 0LL)
		{
			propagation(node, l, r, lazy[node]);
			tree[node] += ((r-l+1) * lazy[node]);
			lazy[node] = 0LL;
		}
		if (b < l || r < a) return 0LL;
		if (a <= l && r <= b) return tree[node];

		const int mid = (l+r)/2;
		return query(node * 2, l, mid, a, b) + query(node*2+1, mid+1, r, a, b);
	}

	ll update(const int node, const int l, const int r, const int & a, const int & b, const ll & d)
	{
		if (lazy[node] != 0LL)
		{
			propagation(node, l, r, lazy[node]);
			tree[node] += ((r-l+1) * lazy[node]);
			lazy[node] = 0LL;
		}
		if (b < l || r < a) return tree[node];
		if (a <= l && r <= b)
		{
			propagation(node, l, r, d);
			return tree[node] += ((r-l+1) * d);
		}

		const int mid = (l+r)/2;
		return tree[node] = update(node*2, l, mid, a, b, d) + update(node*2+1, mid+1, r, a, b, d);
	}

	void propagation(const int & node, const int & l, const int & r, const ll & d)
	{
		if (l < r)
		{
			lazy[node * 2] += d;
			lazy[node * 2 + 1] += d;
		}
	}
};

int n, m, k;
VI vi;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %d", &n, &m, &k); m+=k;
	
	vi = VI(n);
	for (int i = 0; i<n; ++i) scanf("%lld", &vi[i]);
	SEGTREE segtree(vi);

	while (m--)
	{
		int select, a, b;
		ll d;

		scanf("%d", &select);
		switch (select)
		{
		case 1: // update
			scanf("%d %d %lld", &a, &b, &d);
			segtree.update(a-1, b-1, d);
			break;
		case 2: // dply sum
			scanf("%d %d", &a, &b);
			printf("%lld\n", segtree.query(a-1, b-1));
			break;
		}
	}
	return 0;
}
