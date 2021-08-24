#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> map;

int getDiff(int x, int y, int d1, int d2) {
	vector<vector<int>> subMap(n, vector<int>(n));
	vector<int> cnt(5, 0);
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (0 <= r && r < x + d1 && 0 <= c && c <= y) subMap[r][c] = 0;
			if (0 <= r && r <= x + d2 && y < c && c < n) subMap[r][c] = 1;
			if (x + d1 <= r && r < n && 0 <= c && c < y - d1 + d2) subMap[r][c] = 2;
			if (x + d2 < r && r < n && y - d1 + d2 <= c && c < n) subMap[r][c] = 3;
		}
	}
	for (int i = 0; i <= d1; ++i) {
		subMap[x + i][y - i] = 4;
		subMap[x + d2 + i][y + d2 - i] = 4;
	}
	for (int i = 0; i <= d2; ++i) {
		subMap[x + i][y + i] = 4;
		subMap[x + d1 + i][y - d1 + i] = 4;
	}
	for (int i = x + 1; i < x + d1 + d2; ++i) {
		bool in = false;
		for (int j = 0; j < n; ++j) {
			if (subMap[i][j] == 4) in = !in;
			if (in) subMap[i][j] = 4;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cnt[subMap[i][j]] += map[i][j];
		}
	}
	int mini = cnt[0], maxi = cnt[0];
	for (int i = 1; i < cnt.size(); ++i) {
		mini = min(mini, cnt[i]);
		maxi = max(maxi, cnt[i]);
	}
	return maxi - mini;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n;
	map = vector<vector<int>>(n, vector<int>(n));
	int opt = 987654321;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j];
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			for (int d1 = 1; d1 < n; ++d1) {
				for (int d2 = 1; d2 < n; ++d2) {
					if (d1 + d2 <= 0 || x + d1 + d2 >= n || y - d1 < 0 || y + d2 >= n) continue;
					opt = min(opt, getDiff(x, y, d1, d2));
				}
			}
		}
	}
	cout << opt;
	return 0;
}