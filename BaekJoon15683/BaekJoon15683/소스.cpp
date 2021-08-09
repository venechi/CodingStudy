#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m;
vector<vector<int>> map;

int cntBlindSpots() {
	int cnt = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)if (map[i][j] == 0)++cnt;
	return cnt;
}

void extract(int x, int y, int d) {
	if ((d & 1) == 1) {//north
		for (int k = x - 1; k >= 0; --k) {
			if (map[k][y] == 6) break;
			if (map[k][y] % 11 == 0) map[k][y] += 11;
		}
	}
	if ((d & 2) == 2) {//east
		for (int k = y + 1; k < m; ++k) {
			if (map[x][k] == 6) break;
			if (map[x][k] % 11 == 0) map[x][k] += 11;
		}
	}
	if ((d & 4) == 4) {//south
		for (int k = x + 1; k < n; ++k) {
			if (map[k][y] == 6) break;
			if (map[k][y] % 11 == 0) map[k][y] += 11;
		}
	}
	if ((d & 8) == 8) {//west
		for (int k = y - 1; k >= 0; --k) {
			if (map[x][k] == 6) break;
			if (map[x][k] % 11 == 0) map[x][k] += 11;
		}
	}
}

void distract(int x, int y, int d) {
	if ((d & 1) == 1) {//north
		for (int k = x - 1; k >= 0; --k) {
			if (map[k][y] == 6) break;
			if (map[k][y] % 11 == 0) map[k][y] -= 11;
		}
	}
	if ((d & 2) == 2) {//east
		for (int k = y + 1; k < m; ++k) {
			if (map[x][k] == 6) break;
			if (map[x][k] % 11 == 0) map[x][k] -= 11;
		}
	}
	if ((d & 4) == 4) {//south
		for (int k = x + 1; k < n; ++k) {
			if (map[k][y] == 6) break;
			if (map[k][y] % 11 == 0) map[k][y] -= 11;
		}
	}
	if ((d & 8) == 8) {//west
		for (int k = y - 1; k >= 0; --k) {
			if (map[x][k] == 6) break;
			if (map[x][k] % 11 == 0) map[x][k] -= 11;
		}
	}
}

int rec_func(int x, int y) {
	if (x == n) return cntBlindSpots();
	int nextX, nextY, opt = 64;
	if (y == m - 1) nextX = x + 1, nextY = 0;
	else nextX = x, nextY = y + 1;
	switch (map[x][y]) {
	case 1:
		for (int i = 0; i < 4; ++i) {
			extract(x, y, pow(2, i));
			opt = min(opt, rec_func(nextX, nextY));
			distract(x, y, pow(2, i));
		}
		return opt;
	case 2:
		for (int i = 0; i < 2; ++i) {
			int d = pow(2, i) + pow(2, i + 2);
			extract(x, y, d);
			opt = min(opt, rec_func(nextX, nextY));
			distract(x, y, d);
		}
		return opt;
	case 3:
		for (int i = 0; i < 4; ++i) {
			int d = pow(2, i) + pow(2, (i + 1) % 4);
			extract(x, y, d);
			opt = min(opt, rec_func(nextX, nextY));
			distract(x, y, d);
		}
		return opt;
	case 4:
		for (int i = 0; i < 4; ++i) {
			int d = pow(2, i) + pow(2, (i + 1) % 4) + pow(2, (i + 2) % 4);
			extract(x, y, d);
			opt = min(opt, rec_func(nextX, nextY));
			distract(x, y, d);
		}
		return opt;
	default:
		return rec_func(nextX, nextY);
	}
}

void expand5() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == 5) {
				extract(i, j, 15);
			}
		}
	}
}

int main(void) {
	cin >> n >> m;
	map = vector<vector<int>>(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)cin >> map[i][j];
	expand5();
	cout << rec_func(0, 0) << endl;
	return 0;
}