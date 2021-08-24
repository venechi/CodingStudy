#include <iostream>
#include <vector>

using namespace std;

class board {
private:
	int score;
	vector<vector<int>> map;

	void dragUpperLines(int line) {
		for (int i = line; i > 0; --i) {
			for (int j = 0; j < 4; ++j) {
				map[i][j] = map[i - 1][j];
				map[i - 1][j] = 0;
			}
		}
	}

	void checkScore() {
		for (int i = 2; i < 6; ++i) {
			int cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (map[i][j] == 1) ++cnt;
			}
			if (cnt == 4) {
				++score;
				EraseLine(i);
			}
		}
	}

	void EraseLine(int line) {
		for (int i = 0; i < 4; ++i) map[line][i] = 0;
		dragUpperLines(line);
	}

	void checkBlockIntheSpecialRegion() {
		for (int i = 0; i < 4; ++i) {
			if (map[0][i] != 0) {
				EraseLine(4);
				EraseLine(5);
				return;
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (map[1][i] != 0) {
				EraseLine(5);
				return;
			}
		}
	}

public:
	board() {
		score = 0;
		map = vector<vector<int>>(6, vector<int>(4, 0));
	}

	void setTile(int type, int line) {
		if (type == 1) {
			map[1][line] = 1;
			for (int k = 2; k < 6; ++k) {
				if (map[k][line] == 0) {
					map[k][line] = 1;
					map[k - 1][line] = 0;
				}
				else break;
			}
		}
		if (type == 2) {
			map[1][line] = map[1][line + 1] = 1;
			for (int k = 2; k < 6; ++k) {
				if (map[k][line] == 0 && map[k][line + 1] == 0) {
					map[k][line] = map[k][line + 1] = 1;
					map[k - 1][line] = map[k - 1][line + 1] = 0;
				}
				else break;
			}
		}
		if (type == 3) {
			map[0][line] = map[1][line] = 1;
			for (int k = 2; k < 6; ++k) {
				if (map[k][line] == 0) {
					map[k][line] = 1;
					map[k - 2][line] = 0;
				}
				else break;
			}
		}

		checkScore();
		checkBlockIntheSpecialRegion();
	}

	int getScore() {
		return score;
	}

	int getBlockCount() {
		int cnt = 0;
		for (int i = 2; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (map[i][j] == 1) ++cnt;
			}
		}
		return cnt;
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	int n;
	board green, blue;
	cin >> n;
	int t, x, y;
	for (int i = 0; i < n; ++i) {
		cin >> t >> x >> y;
		green.setTile(t, y);
		switch (t) {
		case 1:
			blue.setTile(t, 3 - x);
			break;
		case 2:
			blue.setTile(3, 3 - x);
			break;
		case 3:
			blue.setTile(2, 3 - (x + 1));
			break;
		}
	}
	cout << green.getScore() + blue.getScore() << "\n" << green.getBlockCount() + blue.getBlockCount();
}