#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> directions = {
	{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}
};

void move(int sx, int sy, vector<vector<pair<int, int>>>& map) {
	vector<pair<int, int>> fish(17, { -1,-1 });
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if(map[i][j].first != 0)
				fish[map[i][j].first] = { i,j };
		}
	}
	for (int i = 0; i < fish.size(); ++i) {
		if (fish[i].first == -1) continue;
		int x = fish[i].first;
		int y = fish[i].second;
		for (int j = 0; j < 8; ++j) {
			int calX = x + directions[map[x][y].second].first, calY = y + directions[map[x][y].second].second;
			if (calX < 0 || calX >= 4 || calY < 0 || calY >= 4 || (calX == sx && calY == sy)) {
				map[x][y].second = (map[x][y].second + 1) % 8;
				continue;
			}
			fish[map[calX][calY].first] = { x,y };
			pair<int, int> temp = map[x][y];
			map[x][y] = map[calX][calY];
			map[calX][calY] = temp;
			break;
		}
	}
};

int getMax(int sx, int sy, vector<vector<pair<int,int>>> map) {
	int curScore = map[sx][sy].first;
	map[sx][sy].first = 0;
	move(sx, sy, map);
	pair<int, int>& d = directions[map[sx][sy].second];
	int sum = 0;
	for (int i = 1; i <= 4; ++i) {
		int calX = sx + d.first * i, calY = sy + d.second * i;
		if (calX < 0 || calX >= 4 || calY < 0 || calY >= 4) break;
		if (map[calX][calY].first == 0) continue;
		sum = max(sum, getMax(calX, calY, map));
	}
	return curScore + sum;
}

// empty = 0;
int main(void) {
	ios::sync_with_stdio(false);
	vector<vector<pair<int, int>>> map(4, vector<pair<int, int>>(4));
	for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
		cin >> map[i][j].first >> map[i][j].second;
		--map[i][j].second;
	}
	cout << getMax(0, 0, map) << endl;
	return 0;
}