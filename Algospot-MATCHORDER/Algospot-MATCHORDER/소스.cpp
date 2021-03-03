#include <iostream>
#include <algorithm>

using namespace std;

enum {
	ENEMY = 0,
	ALLY = 1
};
int ratings[2][100];
int n;

int maxWin() {
	sort(ratings[ENEMY], ratings[ENEMY] + n);
	sort(ratings[ALLY], ratings[ALLY] + n);
	int wins = 0;
	//�������� �����Ͽ� ���� �̱� �� �����鼭 ���� ���� �������� ���� ������ ������Ų��.
	//���ĵǾ��� ������ �Ʊ��� ��� ������ �˻�Ǹ� �� �̻� �̱� �� �ִ� ���� ����.
	for (int i = 0, j = 0; i < n && j < n; ++i, ++j) {
		if (ratings[ENEMY][i] <= ratings[ALLY][j])
			++wins;
		else
			--i;
	}
	return wins;
}

int main(void) {
	int testcase;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> ratings[i][j];
		}
		cout << maxWin() << endl;
	} while (--testcase);
	return 0;
}