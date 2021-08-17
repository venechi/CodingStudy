#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 987654321;

int n;

vector<vector<int>> map;

vector<pair<int, int>> coords = {
	      {-1,0},
	{0,-1},     {0,1},
	       {1,0}
};

class cmp {
public:
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[2] > b[2];
	}
};

int measureTime(vector<vector<int>> trial) {
	priority_queue<vector<int>, vector<vector<int>>, cmp> q;
	vector < vector<bool>> visited(n, vector<bool>(n, false));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (trial[i][j] == 3) {
		q.push({ i,j,0 });
		visited[i][j] = true;
	}
	int sec = 0;
	while (!q.empty()) {
		vector<int> cur = q.top(); q.pop();
		if (trial[cur[0]][cur[1]] == 3) sec = cur[2];
		for (int i = 0; i < coords.size(); ++i) {
			int calX = cur[0] + coords[i].first, calY = cur[1] + coords[i].second;
			if (calX < 0 || calX >= n || calY < 0 || calY >= n)continue;
			if (trial[calX][calY] == 0 || trial[calX][calY] == 2) {
				if (!visited[calX][calY]) {
					visited[calX][calY] = true;
					if (trial[calX][calY] == 0) trial[calX][calY] = 3;
					q.push({ calX,calY,cur[2] + 1 });
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)if (trial[i][j] == 0) return INF;
	return sec;
}

int getMinSpreadingTime(int x, int y, int leftVirus) {
	if (leftVirus == 0) return measureTime(map);
	if (x == n) return INF;
	int nextX, nextY;
	if (y == n - 1) {
		nextX = x + 1, nextY = 0;
	}
	else {
		nextX = x, nextY = y + 1;
	}
	if (map[x][y] == 2) {
		int ifPass = getMinSpreadingTime(nextX, nextY, leftVirus);
		map[x][y] = 3;
		int ans = min(ifPass, getMinSpreadingTime(nextX, nextY, leftVirus - 1));
		map[x][y] = 2;
		return ans;
	}
	else return getMinSpreadingTime(nextX, nextY, leftVirus);
}

int main(void) {
	int m;
	cin >> n >> m;
	map = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)cin >> map[i][j];
	int ans = getMinSpreadingTime(0, 0, m);
	if (ans == INF) cout << -1;
	else cout << ans;
	return 0;
}