#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> map;

vector<pair<int, int>> coords = {
	      {-1,0},
	{0,-1},     {0,1},
	       {1,0}
};

int cntSafeArea(vector<vector<int>> trial) {
	queue<pair<int, int>> viruses;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (trial[i][j] == 2) viruses.push({ i,j });
	pair<int, int> cur;
	while (!viruses.empty()) {
		cur = viruses.front(); viruses.pop();
		for (int i = 0; i < coords.size(); ++i) {
			int calX = cur.first + coords[i].first;
			int calY = cur.second + coords[i].second;
			if (calX < 0 || calX >= n || calY < 0 || calY >= m) continue;
			if (trial[calX][calY] == 0) {
				trial[calX][calY] = 2;
				viruses.push({ calX,calY });
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (trial[i][j] == 0) ++cnt;
	return cnt;
}

int getMaxSafeArea(int x, int y, int leftWalls) {
	if (leftWalls == 0) return cntSafeArea(map);
	if (x == n) return -1;
	
	int nextX, nextY;
	if (y == m - 1) {
		nextX = x + 1;
		nextY = 0;
	}
	else {
		nextX = x;
		nextY = y + 1;
	}

	if (map[x][y] != 0) return getMaxSafeArea(nextX, nextY, leftWalls);
	map[x][y] = 1;
	int ifWall = getMaxSafeArea(nextX, nextY, leftWalls - 1);
	map[x][y] = 0;
	return max(ifWall, getMaxSafeArea(nextX, nextY, leftWalls));
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	map = vector<vector<int>>(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)cin >> map[i][j];
	cout << getMaxSafeArea(0, 0, 3) << endl;
	return 0;
}