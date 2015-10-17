/*************************************************************************************

2015.10.17
https://www.acmicpc.net/problem/1086

- input : �ִ� 50�ڸ����� ���� �ٸ� �ڿ��� N��(<=15), K(<=100)
- output : N���� ���� ������ ������ �����Ͽ� ���� �ڿ����� ��, K�� ������ �������� ����� ��
- issue :
	1. �� ���ڰ� �ִ� 50�ڸ� �̹Ƿ�, ������ �ڷ����� ������ �� ����
	2. ���ڸ� �����ϴ� ��� ����� �� == N! (15!. �� 1�� 3õ��)

- solution :
	1. �ڿ��� A, B�� ���Ͽ� B�� �ڸ����� L�̶�� �� ��, A�� B�� �����Ͽ� ���� �ڿ����� K�� ���� ��������
	   (A*10^L + B) % K == ( (A % K) * 10^L + B ) % K.
	   ��, �տ������� ���ڸ� �ϳ��� ������ ������ �����鼭 �Ź� ������ ���� ����. (counting�Լ� ��� ȣ��κ�)

	2. ��� ����� ���� �ִ� 15!������, ���������� �ߺ��� �߻�.
	   ����, 26���� �ڿ��� A~Z�� ���Ͽ� �̵��� �����Ͽ� ���� �ڿ��� ��,
	   ..IJABCD�� ..XYABCD����, [ABCD]�� ���� ���ʿ� ������ �����ϴµ�,
	   �̷� ��쿡 ���� ABCD�� K�� ���� �������� �Ź� �ߺ��ؼ� ����� �ʿ䰡 ����.

- complexity : O( 2^n * k )

*************************************************************************************/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef long long ll;

int n, mod, complete; // complete == �� �ڿ����� ��뿩�θ� bitmask�� ǥ������ ��, ��� �ڿ����� ����� ���¸� ǥ��
ll cache[1 << 15][100]; // memoization table
ll tenMod[52]; // tenMod[e] == 10^e�� mod�� ���� ������
ll numMod[15]; // numMod[i] == i��° ���� mod�� ���� ������
string num[15];

// return the GCD(a, b)
ll GCD(ll a, ll b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

// return the N!
ll factorial(const ll & n)
{
	ll ret = 1;
	for (ll i=2; i<=n; ++i) ret *= i;
	return ret;
}

void init()
{
	complete = (1<<n)-1; // N���� �ڿ����� ��� ��������� ��Ÿ���� ���� (bit-mask)
	memset(cache, -1, sizeof(cache)); // memoization table initialize

	tenMod[0] = 1; // 1 % mod == 1
	for (int i = 1; i <= 50; ++i)
		tenMod[i] = (tenMod[i-1]*10) % mod;

	// �� ���� num[i]�� mod�� ���� �������� ���
	for (int i = 0; i < n; ++i)
	{
		int r = 0;
		for (int j = 0; j < num[i].size(); ++j)
		{
			r *= 10;
			r += (num[i][j] - '0');
			r %= mod;
		}
		numMod[i] = r;
	}
}

// ������� ����� ���ڵ��� bitmask�� ǥ���� ���°� state�̰�, ������� ����� �� ������ ���� R�� ��,
// ���� ���ڵ��� ��� ����Ͽ� ������ �ڿ����� mod�� ���� �������� ����� �� ��ȯ
ll counting(const int state, const int R)
{
	if (state == complete) return R == 0 ? 1 : 0;

	ll & ret = cache[state][R];
	if (ret != -1) return ret;
	ret = 0;

	for (int i = 0; i < n; ++i)
	{
		if (state & (1<<i)) continue;
		ret += counting(state|(1<<i), (R * tenMod[num[i].size()] + numMod[i]) % mod);
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
	for (int i=0; i<n; ++i) cin >> num[i];
	scanf("%d", &mod);
	init();
	
	const ll cnt = counting(0, 0); // mod�� ���� �������� ��� ����� ��
	const ll allcase = factorial(n); // N���� ���� �����ϴ� ��� ����� ��(N!)
	const ll gcd = GCD(cnt, allcase);
	printf("%lld/%lld\n", cnt/gcd, allcase/gcd); // ���м��� ���

	return 0;
}
