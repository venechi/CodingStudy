#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	int n, l;
	cin >> n >> l;
	vector<vector<int>> map(n,vector<int>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j];
	int cnt = 0;
	bool OK;
	for (int i = 0; i < n; ++i) {
		OK = true;
		int flatCnt = 1;
		bool down = false;
		for (int k = 1; k < n; ++k) {
			if (map[i][k - 1] == map[i][k]) {
				++flatCnt;
				if (down) {
					if (flatCnt >= l) {
						down = false;
						flatCnt -= l;
					}
				}
			}
			else if (map[i][k - 1] < map[i][k]) {
				if (map[i][k - 1] + 1 == map[i][k] && !down && flatCnt >= l) flatCnt = 1;
				else {
					OK = false;
					break;
				}
			}
			else {
				if (map[i][k - 1] == map[i][k] + 1) {
					if (down) {
						if (flatCnt == l) {
							flatCnt = 1;
						}
						else {
							OK = false;
							break;
						}
					}
					else {
						down = true;
						flatCnt = 1;
					}
				}
				else {
					OK = false;
					break;
				}
			}
		}
		if (OK) {
			if (down) {
				if (flatCnt >= l)
					++cnt;
			}
			else ++cnt;
		}
	}
	for (int j = 0; j < n; ++j) {
		OK = true;
		int flatCnt = 1;
		bool down = false;
		for (int k = 1; k < n; ++k) {
			if (map[k - 1][j] == map[k][j]) {
				++flatCnt;
				if (down) {
					if (flatCnt >= l) {
						down = false;
						flatCnt -= l;
					}
				}
			}
			else if (map[k - 1][j] < map[k][j]) {
				if (map[k - 1][j] + 1 == map[k][j] && !down && flatCnt >= l) flatCnt = 1;
				else {
					OK = false;
					break;
				}
			}
			else {
				if (map[k - 1][j] == map[k][j] + 1) {
					if (down) {
						if (flatCnt == l) {
							flatCnt = 1;
						}
						else {
							OK = false;
							break;
						}
					}
					else {
						down = true;
						flatCnt = 1;
					}
				}
				else {
					OK = false;
					break;
				}
			}
		}
		if (OK) {
			if (down) {
				if (flatCnt >= l)
					++cnt;
			}
			else ++cnt;
		}
	}
	cout << cnt << endl;
	return 0;
 }