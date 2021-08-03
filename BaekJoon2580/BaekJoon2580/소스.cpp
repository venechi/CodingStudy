#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map(9, vector<int>(9));

bool available(int x, int y, int value) {
	for (int i = 0; i < 9; ++i) {
		if (map[x][i] == value || map[i][y] == value) return false;
	}
	int xFrom, xTo, yFrom, yTo;
	xFrom = xTo = x / 3;
	xFrom *= 3;
	xTo = (xTo + 1) * 3;
	yFrom = yTo = y / 3;
	yFrom *= 3;
	yTo = (yTo + 1) * 3;
	for (int i = xFrom; i < xTo; ++i) {
		for (int j = yFrom; j < yTo; ++j) {
			if (map[i][j] == value) return false;
		}
	}
	return true;
}

bool rec_func(int x,int y) {
	if (x == 9) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				cout << map[i][j] << " ";
			}
			cout << "\n";
		}
		return true;
	}
	else {
		if (map[x][y] == 0) {
			for (int i = 1; i <= 9; ++i) {
				if (available(x, y, i)) {
					map[x][y] = i;
					if (y == 8) {
						if (rec_func(x + 1, 0)) return true;
					}
					else {
						if (rec_func(x, y + 1)) return true;
					}
					map[x][y] = 0;
				}
			}
			return false;
		}
		else {
			if (y == 8) return rec_func(x + 1, 0);
			else return rec_func(x, y + 1);
		}
	}
}

int main(void) {
	for (int i = 0; i < 9; ++i)for (int j = 0; j < 9; ++j)cin >> map[i][j];
	rec_func(0, 0);
	return 0;
}