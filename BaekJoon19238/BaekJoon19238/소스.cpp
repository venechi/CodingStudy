#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> coords = {
		  {-1,0},
	{0,-1},		{0,1},
		   {1,0}
};

int n, m, fuel;
vector<vector<int>> map;
vector<pair<int, int>> destinations;
int x, y;

class findCustomer {
public:
	bool operator()(const vector<int>& a, const vector<int>& b) {
		if (a[0] == b[0]) {
			if (a[1] == b[1]) return a[2] > b[2];
			else return a[1] > b[1];
		}
		else return a[0] > b[0];
	}
};

class findPath {
public:
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[0] > b[0];
	}
};

int getPathLength() {
	pair<int, int>& dest = destinations[map[x][y] - 10];
	priority_queue<vector<int>, vector<vector<int>>, findPath> pq;
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	visited[x][y] = true;
	pq.push({ 0,x,y });
	while (!pq.empty()) {
		vector<int> cur = pq.top(); pq.pop();
		if (cur[1] == dest.first && cur[2] == dest.second) return cur[0];
		for (int j = 0; j < coords.size(); ++j) {
			int calX = cur[1] + coords[j].first, calY = cur[2] + coords[j].second;
			if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
			if (visited[calX][calY] || map[calX][calY] == 1) continue;
			visited[calX][calY] = true;
			pq.push({ cur[0] + 1, calX,calY });
		}
	}
	return -1;
}

int getLastFuel() {
	for (int i = 0; i < m; ++i) {
		priority_queue<vector<int>, vector<vector<int>>, findCustomer> pq;
		pq.push({ 0,x,y });
		vector<vector<bool>> visited(n, vector<bool>(n, false));
		visited[x][y] = true;
		bool find = false;
		while (!pq.empty()) {
			vector<int> cur = pq.top(); pq.pop();
			if (map[cur[1]][cur[2]] >= 10) {
				find = true;
				x = cur[1];
				y = cur[2];
				fuel -= cur[0];
				if (fuel <= 0) return -1;
				int length = getPathLength();
				if (length == -1) return -1;
				pair<int, int>& dest = destinations[map[x][y] - 10];
				map[cur[1]][cur[2]] = 0;
				if (fuel >= length) fuel += length;
				else return -1;
				x = dest.first;
				y = dest.second;
				break;
			}
			for (int j = 0; j < coords.size(); ++j) {
				int calX = cur[1] + coords[j].first, calY = cur[2] + coords[j].second;
				if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
				if (visited[calX][calY] || map[calX][calY] == 1) continue;
				visited[calX][calY] = true;
				pq.push({ cur[0] + 1,calX,calY });
			}
		}
		if (!find) return -1;
	}
	return fuel;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> m >> fuel;
	map = vector<vector<int>>(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)cin >> map[i][j];
	cin >> x >> y;
	--x;
	--y;
	int sx, sy, dx, dy;
	for (int i = 0; i < m; ++i) {
		cin >> sx >> sy >> dx >> dy;
		map[sx - 1][sy - 1] = destinations.size() + 10;
		destinations.push_back({ dx - 1,dy - 1 });
	}
	cout << getLastFuel() << endl;
	return 0;
}