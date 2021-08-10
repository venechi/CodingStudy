#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int m;
vector<bool> virtualEdges;
vector<vector<int>> distances;

int getD(const pair<int, int>& a, const pair<int, int>& b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void makeGraph(const vector<vector<int>>& map) {
	vector<pair<int, int>> chickenPlaces;
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == 2) {
				chickenPlaces.push_back({ i,j });
			}
		}
	}
	distances = vector<vector<int>>(chickenPlaces.size(), vector<int>());
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == 1) {
				for (int k = 0; k < distances.size(); ++k) {
					distances[k].push_back(getD({ i,j }, chickenPlaces[k]));
				}
			}
		}
	}
	virtualEdges = vector<bool>(chickenPlaces.size(), false);
}

int getChickenD() {
	vector<int> d(distances[0].size(), 987654321);
	for (int i = 0; i < d.size(); ++i) {
		for (int j = 0; j < distances.size(); ++j) {
			if (virtualEdges[j]) {
				d[i] = min(d[i], distances[j][i]);
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < d.size(); ++i) sum += d[i];
	return sum;
}

int getMinChickenD(int cur, int left) {
	if (cur > distances.size() || left < 0) return 987654321;
	if (cur == distances.size()) {
		if (left == m) return 987654321;
		else return getChickenD();
	}
	if (left == 0) return getChickenD();
	else {
		int ifNotChoose = getMinChickenD(cur + 1, left);
		virtualEdges[cur] = true;
		int ans = min(ifNotChoose, getMinChickenD(cur + 1, left - 1));
		virtualEdges[cur] = false;
		return ans;
	}
}

int main(void) {
	int n;
	cin >> n >> m;
	vector<vector<int>> map(n, vector<int>(n));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)cin >> map[i][j];
	makeGraph(map);
	cout << getMinChickenD(0, m) << endl;
	return 0;
}