#include <iostream>
#include <vector>

using namespace std;

int n;

vector<pair<int, int>> coords = {
		   {-1,0},
	{0,-1},		  {0,1},
			{1,0}
};

void moveOne(vector<vector<int>>& map, vector<vector<bool>>& collapsed, int d, int x, int y) {
	pair<int, int> cur = { x,y };
	pair<int, int> next = { x + coords[d].first, y + coords[d].second };
	while (!(next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)) {
		if (map[next.first][next.second] == 0) {
			map[next.first][next.second] = map[cur.first][cur.second];
			map[cur.first][cur.second] = 0;
		}
		else if (map[next.first][next.second] == map[cur.first][cur.second]) {
			if (!collapsed[next.first][next.second]) {
				map[next.first][next.second] *= 2;
				map[cur.first][cur.second] = 0;
				collapsed[next.first][next.second] = true;
			}
			break;
		}
		else break;
		cur = next;
		next = { cur.first + coords[d].first, cur.second + coords[d].second };
	}
}

void move(vector<vector<int>>& map, int d) {
	vector<vector<bool>> collapsed(n, vector<bool>(n, false));
	switch (d) {
	case 0:
		//up
		for (int i = 1; i < n; ++i) for (int j = 0; j < n; ++j) moveOne(map, collapsed, d, i, j);
		break;
	case 1:
		//left
		for (int i = 0; i < n; ++i) for (int j = 1; j < n; ++j) moveOne(map, collapsed, d, i, j);
		break;
	case 2:
		//right
		for (int i = 0; i < n; ++i) for (int j = n - 2; j >= 0; --j) moveOne(map, collapsed, d, i, j);
		break;
	case 3:
		//down
		for (int i = n - 2; i >= 0; --i) for (int j = 0; j < n; ++j) moveOne(map, collapsed, d, i, j);
		break;
	}
}

int getMax(const vector<vector<int>>& map) {
	int high = 0;
	for (int i = 0; i < n; ++i)	for (int j = 0; j < n; ++j) high = max(high, map[i][j]);
	return high;
}

int rec_func(const vector<vector<int>>& map, int cnt) {
	int high = getMax(map);
	if (cnt != 5) {
		for (int i = 0; i < 4; ++i) {
			vector<vector<int>>next = map;
			move(next, i);
			high = max(high, rec_func(next, cnt + 1));
		}
	}
	return high;
}

int main(void) {
	cin >> n;
	vector<vector<int>> map(n, vector<int>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)cin >> map[i][j];
	cout << rec_func(map, 0);
	return 0;
}