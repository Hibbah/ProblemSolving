/**********************************************************************************************

2015.11.14
http://codeforces.com/contest/598/problem/C

- input : ��ǥ��鿡�� ������ ���������ϴ� N(<=100,000)���� ����(x, y). (��� ���ʹ� ������ �ٸ�)
- output : ���͵��� �Է¹޴� ������� 1~N���� ��ȣ�� �ٿ��� ��, ���� ����� �� ������ ��ȣ
- solution : ���� v(1, 0)�� �������� �ϴ� ����(0~180)�� ����Ͽ� �����ϰ� ���� ��
- issue : ������ ��� => m<ath.h> �� ���� �ﰢ�Լ�(�Ű�����, ��ȯ�� ����)�� Ȱ��
- time complexity : O( NlogN ). (���Ľð�)

**********************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<double, int> ITEM;
#define DEG first
#define NUM second

const double PI = acos(-1); // PI�� ���

int n, x, y;
vector <ITEM> list;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	list.resize(n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d", &x, &y);
		double deg = atan2l(y, x) * 180.0/PI; // degree������ ��ȯ
		if (deg < 0) deg += 360.0; // atan2�� ��ȯ���� [-PI, PI]�̹Ƿ� ���� ũ�� ����
		list[i].DEG = deg;
		list[i].NUM = i+1; // ������ ��ȣ
	}
	sort(list.begin(), list.end());
	list.push_back({ list.front().DEG + 360.0, list.front().NUM });
	
	int a, b;
	double minn = 999999999.0;
	for (int i = 1; i <= n; ++i)
	{
		double sub = list[i].DEG - list[i - 1].DEG; // �� ���Ͱ� �̷�� ����
		if (sub < minn) // �� �������, ����
		{
			minn = list[i].DEG - list[i-1].DEG;
			a = list[i].NUM;
			b = list[i-1].NUM;
		}
	}
	printf("%d %d\n", a, b);

	return 0;
}
