/**********************************************************************************

2015.09.06
https://www.acmicpc.net/problem/10258
(ACMICPC Asia Regional - Daejeon Internet Competition 2014 problem J)

- title : Switch Array
- input : 0/1�� ������ ������ B. (2 <= |B| <= 31)
- output : B�� 0���� ����� ���� �ʿ��� �ּ� ���� Ƚ��
- operation : 
	1. ���� �����ʿ� �ִ� ��Ʈ�� �����Ӱ� toggle ����.
	2. (���ʺ���)��Ʈi�� toggle��Ű�� ���ؼ��� ��Ʈi+1�� �ݵ�� '1'�̰�, i+1������ ��� ��Ʈ�� '0'�̾�� ��.
- solution :
	1. B -> 0�� �ƴ�, 0 -> B�� ����� �ּ� Ƚ���� ���.
	2. Ư�� ��Ʈ�� toggle��Ű�� ���ؼ��� �ش� ��Ʈ�� ������ �����ϴ� ��Ʈ�鸸 �ʿ�.
	   ��, ���� ���ʿ� �ִ� ��Ʈ���� �����ؼ� �� �� ���� ��Ʈ�� �ٽ� ������ �ʿ䰡 ����.
	4. ���� �������� 0��°�� �������� ��, ��Ʈi�� toggle��Ű�� ���� �ּ� ���� Ƚ�� == 2^i
	   ��, ��Ʈi�� toggle������ ��, ��Ʈi+1�� �׻� '1'�̰� ������ ��� ��Ʈ�z '0'.
	5. �ʱ� ���ڿ��� str = "00...000"���� ����, str�� B�� ���������, ���� ���� ��Ʈ���� ���ʴ�� ��ȯ.
	   str[i] != B[i]�� ���, str[i]�� toggle��Ű�� ���� 2^i�� ������ �ʿ��ϰ�, �� �� str[i+1] = '1'�� ��ȯ.
- Complexity : O(|B|)

***********************************************************************************/

#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int t;
ll toggleCnt[31] = { 1, 2 }; // �����ʿ������� i�� bit�� toggle��Ű������ �ʿ��� �ּ� ���� Ƚ��
string B, str;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	for (int i = 2; i < 31; ++i) toggleCnt[i] = toggleCnt[i - 1] * 2;

	scanf("%d", &t);
	while (t--)
	{
		cin >> B;
		str = string(B.length(), '0');

		ll ret = 0;
		for (int i = 0; i < B.length() - 1; ++i)
		{
			if (B[i] != str[i]) // ���ڰ� �ٸ����
			{
				ret += toggleCnt[B.size() - i - 1]; // str[i]�� toggle��Ű�� ���� �ʿ��� �ּ� ���� Ƚ��
				str[i + 1] = '1'; // str[i]�� toggle��Ű�� ��, str[i+1]�� �ݵ�� '1'
			}
		}
		if (B.back() != str.back()) ++ret;
		printf("%lld\n", ret);
	}
	return 0;
}
