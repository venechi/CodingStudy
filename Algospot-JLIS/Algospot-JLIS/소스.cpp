#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

//�޸������̼� �迭
int JLIS[101][101];
//�Է¹迭
int aList[101], bList[101];
//�Է� ���� ����
int n, m;

int getJLIS(int a, int b, long long int lastValue) {
	if (JLIS[a][b] != -1) return JLIS[a][b];
	//��� ���� ���� �ϳ�¥�� �迭�� �׻� �����ϹǷ� ret = 1�� ����.
	int ret = 1;
	//������ ������ ������ ���Һ��� ū ���� ������ subList���� ������� ���ȣ��
	for (int i = a + 1; i <= n; ++i) {
		if (aList[i] > lastValue)
			ret = max<int>(ret, getJLIS(i, b, aList[i]) + 1);
	}
	for (int i = b + 1; i <= m; ++i) {
		if(bList[i] > lastValue)
			ret = max<int>(ret, getJLIS(a, i, bList[i]) + 1);
	}
	return JLIS[a][b] = ret;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i) cin >> aList[i];
		for (int i = 1; i <= m; ++i) cin >> bList[i];
		memset(JLIS, -1, sizeof(int) * 101 * 101);
		//�� �迭�� 0��° ���� ���Ҹ� ���� �� �ش� ���Һ��� ���� ��� ���� �� �ִ� �迭 ���� ����
		//�Է� ������ 32��Ʈ ���� ��ü�̹Ƿ� �׺��� ���� LLONG_MIN�� �ʱⰪ���� ���
		//���� ���Ұ� ���Ե� ������̹Ƿ� ��������� -1 �� ����� ����. 
		cout << getJLIS(0, 0, LLONG_MIN) - 1 << endl;
	}
	return 0;
}