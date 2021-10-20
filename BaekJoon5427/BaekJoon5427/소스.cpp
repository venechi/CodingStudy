#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> directions = {
	{-1,0},
	{0,-1},{0,1},
	{1,0}
};

void burn(vector<vector<char>>& map, vector<pair<int,int>>& fire) {
	vector<pair<int, int>> prevFire = fire;
	fire.clear();
	for (int i = 0; i < prevFire.size(); ++i) {
		for (int j = 0; j < directions.size(); ++j) {
			int calX = prevFire[i].first + directions[j].first, calY = prevFire[i].second + directions[j].second;
			if (calX < 0 || calX >= map.size() || calY < 0 || calY >= map[0].size()) continue;
			if (map[calX][calY] == '.') {
				map[calX][calY] = '*';
				fire.push_back({ calX,calY });
			}
		}
	}
}

int main(void) {
	cin.tie(0);
	int tc;
	cin >> tc;
	for (int tcc = 0; tcc < tc; ++tcc) {
		int w, h;
		int x, y;
		cin >> w >> h;
		vector<vector<char>> map(h, vector<char>(w));
		vector<pair<int, int>> fire;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cin >> map[i][j];
				if (map[i][j] == '*') fire.push_back({ i,j });
				if (map[i][j] == '@') {
					map[i][j] = '.';
					x = i, y = j;
				}
			}
		}
		burn(map, fire);//불이 붙을 곳은 어차피 접근 불가 -> 접근 불가 영역도 불 표시함.
		queue<vector<int>> q;
		q.push({ x,y,0 });
		vector<vector<bool>> visited(h, vector<bool>(w, false));
		visited[x][y] = true;
		bool escaped = false;
		int curStep = 0;
		while (!q.empty() && !escaped) {
			vector<int> cur = q.front(); q.pop();
			if (curStep != cur[2]) {
				curStep = cur[2];
				burn(map, fire);
			}
			for (int i = 0; i < directions.size(); ++i) {
				int calX = cur[0] + directions[i].first, calY = cur[1] + directions[i].second;
				if (calX < 0 || calX >= h || calY < 0 || calY >= w) {
					escaped = true;
					cout << cur[2] + 1 << "\n";
					break;
				}
				if (map[calX][calY] == '.' && !visited[calX][calY]) {
					visited[calX][calY] = true;
					q.push({ calX, calY, cur[2] + 1 });
				}
			}
		}
		if (!escaped) cout << "IMPOSSIBLE\n";
	}
	return 0;
}