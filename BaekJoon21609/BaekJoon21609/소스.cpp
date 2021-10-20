#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> map;
vector<pair<int, int>> coords = {
		  {-1,0},
	{0,-1},		{0,1},
		   {1,0}
};

bool cmp(const vector<int>& a, const vector<int>& b) {
	if (a[0] == b[0]) {
		if (a[1] == b[1]) {
			if (a[2] == b[2]) {
				return a[3] > b[3];
			}
			else return a[2] > b[2];
		}
		else return a[1] > b[1];
	}
	else return a[0] > b[0];
}

vector<vector<int>> getCandidates() {
	vector<vector<int>> candidates;
	vector<vector<bool>> global_visited(map.size(), vector<bool>(map.size(), false));
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map.size(); ++j) {
			if (map[i][j] > 0 && !global_visited[i][j]) {
				vector<vector<bool>> visited(map.size(), vector<bool>(map.size(), false));
				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = global_visited[i][j] = true;
				int bCnt = 1, rCnt = 0;
				while (!q.empty()) {
					pair<int, int> cur = q.front(); q.pop();
					for (int k = 0; k < coords.size(); ++k) {
						int calX = cur.first + coords[k].first, calY = cur.second + coords[k].second;
						if (calX < 0 || calX >= map.size() || calY < 0 || calY >= map.size() || visited[calX][calY]) continue;
						if (map[calX][calY] == 0) ++rCnt;
						else if (map[calX][calY] == map[i][j]) ++bCnt;
						else continue;
						visited[calX][calY] = global_visited[calX][calY] = true;
						q.push({ calX, calY });
					}
				}
				if (bCnt + rCnt >= 2) {
					candidates.push_back({ bCnt + rCnt, rCnt, i, j });
				}
			}
		}
	}
	return candidates;
}

int removeBlockGroup(const vector<int>& info) {
	queue<pair<int, int>> q;
	q.push({ info[2],info[3] });
	int pivot = map[info[2]][info[3]];
	map[info[2]][info[3]] = -2;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int k = 0; k < coords.size(); ++k) {
			int calX = cur.first + coords[k].first, calY = cur.second + coords[k].second;
			if (calX < 0 || calX >= map.size() || calY < 0 || calY >= map.size()) continue;
			if (map[calX][calY] == 0 || map[calX][calY] == pivot) {
				map[calX][calY] = -2;
				q.push({ calX, calY });
			}
		}
	}
	return info[0] * info[0];
}

void gravity() {
	for (int i = map.size() - 2; i >= 0; --i) {
		for (int j = 0; j < map.size(); ++j) {
			if (map[i][j] >= 0) {
				int k = i;
				while (k + 1 < map.size() && map[k + 1][j] == -2) {
					int temp = map[k + 1][j];
					map[k + 1][j] = map[k][j];
					map[k][j] = temp;
					++k;
				}
			}
		}
	}
}

void rotate() {
	vector<vector<int>> temp = map;
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map.size(); ++j) {
			map[map.size() - 1 - j][i] = temp[i][j];
		}
	}
}

int main(void) {
	int n, m;
	cin >> n >> m;
	map = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j];
	vector<vector<int>> candidates;
	int score = 0;
	while (true) {
		candidates = getCandidates();
		if (candidates.size() == 0) break;
		sort(candidates.begin(), candidates.end(), cmp);
		score += removeBlockGroup(candidates[0]);
		gravity();
		rotate();
		gravity();
	}
	cout << score << endl;
	return 0;
}