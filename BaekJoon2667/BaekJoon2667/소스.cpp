#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> map;

vector<pair<int, int>> coords = {
		  {-1,0},
	{0,-1},      {0,1},
		   {1,0}
};

int countNErase(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x,y });
	map[x][y] = 0;
	int cnt = 1;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int i = 0; i < 4; ++i) {
			int calX = cur.first + coords[i].first;
			int calY = cur.second + coords[i].second;
			if (calX < 0 || calX >= map.size() || calY < 0 || calY >= map.size()) continue;
			if (map[calX][calY] == 1) {
				map[calX][calY] = 0;
				++cnt;
				q.push({ calX,calY });
			}
		}
	}
	return cnt;
}

int main(void) {
	int n;
	cin >> n;
	map = vector<vector<int>>(n, vector<int>(n));
	string input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		for (int j = 0; j < input.size(); ++j) {
			map[i][j] = (input[j] - '0');
		}
	}
	vector<int> towns;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j] == 1) {
				towns.push_back(countNErase(i, j));
			}
		}
	}
	cout << towns.size() << "\n";
	sort(towns.begin(), towns.end());
	for (int i = 0; i < towns.size(); ++i) cout << towns[i] << "\n";
	return 0;
}