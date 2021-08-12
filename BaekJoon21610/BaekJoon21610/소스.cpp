#include <iostream>
#include <vector>

using namespace std;

int n;

vector<vector<int>> map;
vector<vector<bool>> cloud;

vector<pair<int, int>> moveCoords = {
	{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}
};

vector<pair<int, int>> copyCoords = {
	{-1,-1}, {-1,1},
	{1,-1}, {1,1}
};

void windEffect(int d, int s) {
	vector<vector<bool>> nextCloud(n, vector<bool>(n, false));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (cloud[i][j]) {
				cloud[i][j] = false;
				int calX = i + (moveCoords[d - 1].first * s), calY = j + (moveCoords[d - 1].second * s);
				calX = (calX + n * 25) % n;
				calY = (calY + n * 25) % n;
				nextCloud[calX][calY] = true;
				++map[calX][calY];
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (nextCloud[i][j]) {
				int cnt = 0;
				for (int k = 0; k < copyCoords.size(); ++k) {
					int calX = i + copyCoords[k].first, calY = j + copyCoords[k].second;
					if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
					if (map[calX][calY] > 0) ++cnt;
				}
				map[i][j] += cnt;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (!nextCloud[i][j] && map[i][j] >= 2) {
				cloud[i][j] = true;
				map[i][j] -= 2;
			}
		}
	}
}

int sumOfWater() {
	int sum = 0;
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)sum += map[i][j];
	return sum;
}

int main(void) {
	ios::sync_with_stdio(false);
	int m, d, s;
	cin >> n >> m;
	map = vector<vector<int>>(n, vector<int>(n));
	cloud = vector<vector<bool>>(n, vector<bool>(n, false));
	cloud[n - 1][0] = cloud[n - 1][1] = cloud[n - 2][0] = cloud[n - 2][1] = true;
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)cin >> map[i][j];
	for (int i = 0; i < m; ++i) {
		cin >> d >> s;
		windEffect(d, s);
	}
	cout << sumOfWater() << endl;
	return 0;
}