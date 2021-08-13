#include <iostream>
#include <vector>

using namespace std;

int r, c;
vector<vector<vector<int>>> map;

vector<pair<int, int>> coords = {
	{-1,0},{1,0},{0,1},{0,-1}
};

void move() {
	vector<vector<vector<int>>> next(r, vector<vector<int>>(c, { 0,0,0 }));
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (map[i][j][1] != 0) {
				int calX, calY, calD;
				bool dChange = false;
				switch (map[i][j][1]) {
				case 1: case 2:
					calY = j;
					calX = i;
					if (map[i][j][1] == 1) {
						calX = r - 1 - i;
					}
					calX = (calX + map[i][j][0]) % ((r - 1) * 2);
					if (calX >= r) {
						calX = (r - 1) * 2 - calX;
						dChange = true;
					}
					if (map[i][j][1] == 1) {
						calX = r - 1 - calX;
						if (dChange) calD = 2;
						else calD = 1;
					}
					else {
						if (dChange) calD = 1;
						else calD = 2;
					}
					break;
				case 3: case 4:
					calX = i;
					calY = j;
					if (map[i][j][1] == 4) {
						calY = c - 1 - j;
					}
					calY = (calY + map[i][j][0]) % ((c - 1) * 2);
					if (calY >= c) {
						calY = (c - 1) * 2 - calY;
						dChange = true;
					}
					if (map[i][j][1] == 4) {
						calY = c - 1 - calY;
						if (dChange) calD = 3;
						else calD = 4;
					}
					else {
						if (dChange) calD = 4;
						else calD = 3;
					}
					break;
				}
				if (next[calX][calY][1] == 0 || next[calX][calY][2] < map[i][j][2]) {
					next[calX][calY] = map[i][j];
					next[calX][calY][1] = calD;
				}
			}
		}
	}
	map = next;
}

int main(void) {
	int m;
	cin >> r >> c >> m;
	map = vector<vector<vector<int>>>(r, vector<vector<int>>(c, { 0,0,0 }));
	int x, y, s, d, z;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> s >> d >> z;
		map[x - 1][y - 1] = { s,d,z };
	}
	int sum = 0;
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < r; ++j) {
			if (map[j][i][1] != 0) {
				sum += map[j][i][2];
				map[j][i] = { 0,0,0 };
				break;
			}
		}
		move();
	}
	cout << sum << endl;
	return 0;
}