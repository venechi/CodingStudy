#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> coords = {
		  {-1,0},
	{0,-1},     {0,1},
		   {1,0}
};

int n, l, r;

vector<vector<int>> map;

bool makeUnion() {
	vector<int> nextPopulation;
	vector<vector<int>> checked(n, vector<int>(n, -1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (checked[i][j] == -1) {
				nextPopulation.push_back(map[i][j]);
				checked[i][j] = nextPopulation.size() - 1;
				queue<pair<int, int>> q;
				q.push({ i,j });
				int cnt = 1;
				while (!q.empty()) {
					pair<int, int> cur = q.front(); q.pop();
					for (int k = 0; k < 4; ++k) {
						int calX = cur.first + coords[k].first, calY = cur.second + coords[k].second;
						if (calX < 0 || calX >= n || calY < 0 || calY >= n)continue;
						if (checked[calX][calY] == -1) {
							int gap = abs(map[cur.first][cur.second] - map[calX][calY]);
							if (gap >= l && gap <= r) {
								++cnt;
								q.push({ calX,calY });
								nextPopulation.back() += map[calX][calY];
								checked[calX][calY] = nextPopulation.size() - 1;
							}
						}
					}
				}
				nextPopulation.back() /= cnt;
			}
		}
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) map[i][j] = nextPopulation[checked[i][j]];
	return (nextPopulation.size() < n * n);
}

int main(void) {
	cin >> n >> l >> r;
	map = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j];
	int days = 0;
	while (makeUnion()) ++days;
	cout << days << endl;
	return 0;
}