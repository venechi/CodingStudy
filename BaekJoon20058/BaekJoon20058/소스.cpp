#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

vector<pair<int, int>> near = {
		   {-1,0},
	{0,-1},		  {0,1},
		    {1,0}
};

int n;
vector<vector<int>> map;

void turn(int x, int y, int size) {
	vector<vector<int>> next(size, vector<int>(size));
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			next[j][size - 1 - i] = map[x + i][y + j];
		}
	}
	for (int i = 0; i < size; ++i) for (int j = 0; j < size; ++j) map[x + i][y + j] = next[i][j];
}

void firestorm(int l) {
	for (int i = 0; i < n; i += l) for (int j = 0; j < n; j += l) turn(i, j, l);
	vector<pair<int, int>> toReduce;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j] > 0) {
				int cnt = 0;
				for (int k = 0; k < near.size(); ++k) {
					int calX = i + near[k].first, calY = j + near[k].second;
					if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
					if (map[calX][calY] > 0) ++cnt;
				}
				if (cnt < 3) toReduce.push_back({ i,j });
			}
		}
	}
	for (int i = 0; i < toReduce.size(); ++i) {
		if (map[toReduce[i].first][toReduce[i].second] > 0)
			--map[toReduce[i].first][toReduce[i].second];
	}
}

vector<int> getSumNColumnsOfTheBiggestGlacial() {
	int sum = 0, maxColumns = 0;
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			sum += map[i][j];
			if (!visited[i][j] && map[i][j] > 0) {
				int cnt = 1;
				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = true;
				while (!q.empty()) {
					pair<int, int> cur = q.front(); q.pop();
					for (int k = 0; k < near.size(); ++k) {
						int calX = cur.first + near[k].first, calY = cur.second + near[k].second;
						if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
						if (!visited[calX][calY] && map[calX][calY] > 0) {
							++cnt;
							visited[calX][calY] = true;
							q.push({ calX,calY });
						}
					}
				}
				maxColumns = max(maxColumns, cnt);
			}
		}
	}
	return { sum, maxColumns };
}

int main(void) {
	ios::sync_with_stdio(false);
	int q, l;
	cin >> n >> q;
	n = pow(2, n);
	map = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)cin >> map[i][j];
	for (int i = 0; i < q; ++i) {
		cin >> l;
		firestorm(pow(2, l));
	}
	vector<int> answer = getSumNColumnsOfTheBiggestGlacial();
	cout << answer[0] << "\n" << answer[1];
	return 0;
}