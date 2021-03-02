#include <iostream>
#include <cstring>

using namespace std;

int n;
int cache[101];
const int MOD = 1000000007;

int tiling2(int start) {
	//Ÿ���� ��Ȯ�� ���̸� 1 ��ȯ(���� ����)
	if (start == n) return 1;
	//Ÿ���� �־��� ������ �Ѿ�� 0 ��ȯ(���� ����)
	if (start == n + 1) return 0;
	int& ret = cache[start];
	if (ret != -1) return ret;
	//a%p + b%p = (a+b)%p �̹Ƿ� �Ʒ� ���� ����
	return ret = (tiling2(start + 1) + tiling2(start + 2)) % MOD;
}

int asymTiling() {
	memset(cache, -1, sizeof(int) * 101);
	int whole = tiling2(0);
	memset(cache, -1, sizeof(int) * 101);
	//��ü ���̰� ¦���� ���, Ÿ���� ��Ī���� �Ǵ� ���� ��ü ������ ����¥�� ���� ä�� Ÿ���� ������ ���¿�
	//�߰��� ���� 2¥�� Ÿ���� ä���ְ� (��ü���� / 2 - 1)¥�� ������ ���� ä�� Ÿ���� ������ ���°� �����Ƿ�
	//�� �� ��츦 ���� ������ ����� ���� Ÿ�ϸ� ����� ���̴�.
	if (n % 2 == 0) {
		n /= 2;
		//��ⷯ ���� ����� ���� ������ ��, �� ���� Ŭ ���ɼ��� �����Ƿ�, ���� ���� ��ⷯ���� ���� �� ����, ������� �ٽ� �ѹ� ��ⷯ ������ ��������
		whole = (whole + MOD - tiling2(0)) % MOD;
		memset(cache, -1, sizeof(int) * 101);
		--n;
		return (whole + MOD - tiling2(0)) % MOD;
	}
	//��ü ���̰� Ȧ���� ���, Ÿ���� ��Ī���� �Ǵ� ���� ��� ���� 1¥�� Ÿ���� ä��� ([��ü���� - 1 ] / 2)¥�� ������ ���� ä�� Ÿ���� ������ ���°� �����Ƿ�
	//��ü ����� ������ �� ��츦 ���� ������ ����� ���� Ÿ�ϸ� ����� ���̴�.
	else {
		n = (n - 1) / 2;
		return (whole + MOD - tiling2(0)) % MOD;
	}
}


int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		
		cout << asymTiling() << endl;
	}
	return 0;
}