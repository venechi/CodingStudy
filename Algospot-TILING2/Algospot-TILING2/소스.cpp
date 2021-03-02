#include <iostream>
#include <cstring>

using namespace std;

int n;
int cache[101];

int tiling2(int start) {
	//Ÿ���� ��Ȯ�� ���̸� 1 ��ȯ(���� ����)
	if (start == n) return 1;
	//Ÿ���� �־��� ������ �Ѿ�� 0 ��ȯ(���� ����)
	if (start == n + 1) return 0;
	int& ret = cache[start];
	if (ret != -1) return ret;
	//a%p + b%p = (a+b)%p �̹Ƿ� �Ʒ� ���� ����
	return ret = (tiling2(start + 1) + tiling2(start + 2)) % 1000000007;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		memset(cache, -1, sizeof(int) * 101);
		cout << tiling2(0) << endl;
	}
	return 0;
}