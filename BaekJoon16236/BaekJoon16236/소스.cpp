#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int sx, sy, sSize = 2, cntFishEaten = 0;
vector<vector<int>> map;

vector<pair<int, int>> coords{
	      {-1,0},
	{0,-1},     {0,1},
	       {1,0}
};

class cmp {
public:
	bool operator()(const vector<int>& a, const vector<int>& b) {
		if (a[0] != b[0]) return a[0] > b[0];
		if (a[1] != b[1]) return a[1] > b[1];
		return a[2] > b[2];
	}
};

//d,x,y
vector<int> findNearestEdibleFish() {
	priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	pq.push({ 0,sx,sy });
	visited[sx][sy] = true;
	while (!pq.empty()) {
		vector<int> cur = pq.top(); pq.pop();
		if (map[cur[1]][cur[2]] != 0 && map[cur[1]][cur[2]] < sSize) return cur;
		for (int i = 0; i < coords.size(); ++i) {
			int calX = cur[1] + coords[i].first, calY = cur[2] + coords[i].second;
			if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
			if (visited[calX][calY]) continue;
			if (map[calX][calY] > sSize) continue;
			pq.push({ cur[0] + 1, calX, calY });
			visited[calX][calY] = true;
		}
	}
	return { -1,-1,-1 };
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n;
	map = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j) {
		cin >> map[i][j];
		if (map[i][j] == 9) {
			map[i][j] = 0;
			sx = i, sy = j;
		}
	}
	int sec = 0;
	while (true) {
		vector<int> next = findNearestEdibleFish();
		if (next[0] == -1) break;
		sec += next[0];
		++cntFishEaten;
		sx = next[1];
		sy = next[2];
		map[sx][sy] = 0;
		if (cntFishEaten == sSize) {
			++sSize;
			cntFishEaten = 0;
		}
	}
	cout << sec << endl;
	return 0;
}