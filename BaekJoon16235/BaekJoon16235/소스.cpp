#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;

vector<vector<int>> A;
vector<vector<vector<int>>> trees;
vector<vector<int>> nutritions;

vector<pair<int, int>> coords{
	{-1,-1},{-1,0},{-1,1},
	{0,-1},        {0,1},
	{1,-1}, {1,0}, {1,1}
};

void growthNDeath() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			vector<int>& cur = trees[i][j];
			sort(cur.begin(), cur.end());
			for (int k = 0; k < cur.size(); ++k) {
				if (nutritions[i][j] >= cur[k]) {
					nutritions[i][j] -= cur[k];
					++cur[k];
				}
				else {
					for (int l = k; l < cur.size(); ++l) {
						nutritions[i][j] += (cur[l] / 2);
					}
					cur.erase(cur.begin() + k, cur.end());
					break;
				}
			}
		}
	}
}

void makeChild() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			vector<int>& cur = trees[i][j];
			for (int k = 0; k < cur.size(); ++k) {
				if (cur[k] % 5 == 0) {
					for (int l = 0; l < coords.size(); ++l) {
						int calX = i + coords[l].first, calY = j + coords[l].second;
						if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
						trees[calX][calY].push_back(1);
					}
				}
			}
		}
	}
}

void addNutritions() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			nutritions[i][j] += A[i][j];
		}
	}
}

int cntTrees() {
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cnt += trees[i][j].size();
		}
	}
	return cnt;
}

int main(void) {
	ios::sync_with_stdio(false);
	int m, k, x, y, z;
	cin >> n >> m >> k;
	A = vector<vector<int>>(n, vector<int>(n));
	nutritions = vector<vector<int>>(n, vector<int>(n, 5));
	trees = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>()));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j) cin >> A[i][j];
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> z;
		trees[x - 1][y - 1].push_back(z);
	}
	for (int i = 0; i < k; ++i) {
		growthNDeath();
		makeChild();
		addNutritions();
	}
	cout << cntTrees() << endl;
	return 0;
}