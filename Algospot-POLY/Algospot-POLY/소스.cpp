#include <iostream>
#include <cstring>

using namespace std;

int cache[101][101];
const int MOD = 10000000;

int poly(int upperLineBlocks, int remainingBlocks) {
	if (remainingBlocks == 0) return 1;
	int& ret = cache[upperLineBlocks][remainingBlocks];
	if (ret != -1)return ret;
	ret = 0;
	for (int size = 1; size <= remainingBlocks; ++size) {
		//���� ������ ���, ù ��° ���ο� ��� �� ���� ���� ����� ���� �ϳ��̹Ƿ� ���� ó��
		if (upperLineBlocks == 0)
			ret = (ret + poly(size, remainingBlocks - size)) % MOD;
		//���� ������ ���� ��� �� �� ��� ������ �Ʒ� �ٿ� ä�� ��� ������ ���� ����� ���� �޶����Ƿ� �ش� ����� ����ŭ ���� ����
		// ex) ���� 2, �Ʒ��� 3���� ���
		//	1) 0 0 1 1 0 0	2) 0 0 1 1 0 0	3) 0 0 1 1 0 0	4) 0 0 1 1 0 0  
		//	   1 1 1 0 0 0	   0 1 1 1 0 0	   0 0 1 1 1 0	   0 0 0 1 1 1
		// �� 4���� ����� ���� ���´�.
		else
			ret = (ret + (poly(size, remainingBlocks - size) * (size + upperLineBlocks - 1)) % MOD) % MOD;
	}
	return ret;
}

int main(void) {
	int testcase, n;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		memset(cache, -1, sizeof(int) * 101 * 101);
		cout << poly(0, n) << endl;
	}
	return 0;
}