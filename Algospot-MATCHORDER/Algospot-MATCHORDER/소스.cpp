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
	//레이팅을 정렬하여 적을 이길 수 있으면서 가장 낮은 레이팅을 갖는 선수를 출전시킨다.
	//정렬되었기 때문에 아군의 모든 선수가 검사되면 더 이상 이길 수 있는 경기는 없다.
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