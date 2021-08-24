#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> map;

vector<pair<int, int>> directions = {
	{-1,0},{0,-1},{1,0},{0,1}
};

vector<vector<int>> portions = {
	{0,0,2,0,0},
	{0,10,7,1,0},
	{5,0,0,0,0},
	{0,10,7,1,0},
	{0,0,2,0,0}
};

void turnPortion() {
	vector<vector<int>> next(5, vector<int>(5, 0));
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			next[4 - j][i] = portions[i][j];
		}
	}
	portions = next;
}

int wind(int x, int y, int d) {
	int out = 0;
	int spread = 0;
	int calX, calY;
	for (int i = -2; i <= 2; ++i) {
		for (int j = -2; j <= 2; ++j) {
			if (portions[i + 2][j + 2] != 0) {
				calX = x + i, calY = y + j;
				if (calX < 0 || calX >= n || calY < 0 || calY >= n) {
					out += (map[x][y] * portions[i + 2][j + 2] / 100);
				}
				else {
					spread += (map[x][y] * portions[i + 2][j + 2] / 100);
					map[calX][calY] += (map[x][y] * portions[i + 2][j + 2] / 100);
				}
			}
		}
	}
	calX = x + directions[d].first;
	calY = y + directions[d].second;
	if (calX < 0 || calX >= n || calY < 0 || calY >= n) {
		out = map[x][y] - spread;
	}
	else {
		map[calX][calY] += (map[x][y] - spread - out);
	}
	map[x][y] = 0;
	return out;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n;
	map = vector<vector<int>>(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)cin >> map[i][j];
	int d = 1;
	int x = n / 2, y = n / 2;
	int dist = 1;
	int cnt = 0;
	int sum = 0;
	while (cnt < n * n) {
		for (int k = 0; k < 2 && cnt < n * n; ++k) {
			for (int l = 0; l < dist; ++l) {
				cnt++;
				if (cnt == n * n) break;
				x += directions[d].first;
				y += directions[d].second;
				sum += wind(x, y, d);
			}
			d = (d + 1) % 4;
			turnPortion();
		}
		dist++;
	}
	cout << sum << endl;
	return 0;
 }