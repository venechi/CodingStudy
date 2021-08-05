#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> map;
deque<pair<int, int>> snake;

vector<pair<int, int>> coords = {
	{-1,0},{0,1},{1,0},{0,-1}
};

int main(void) {
	int n, k;
	cin >> n >> k;
	map = vector<vector<int>>(n + 2, vector<int>(n + 2));
	map[0] = vector<int>(n + 2, 1);
	map.back() = vector<int>(n + 2, 1);
	for (int i = 1; i <= n; ++i) {
		map[i][0] = map[i].back() = 1;
	}
	int x, y;
	for (int i = 0; i < k; ++i) {
		cin >> x >> y;
		map[x][y] = 2;
	}
	queue<pair<int, char>> directions;
	int l;
	int time;
	char direction;
	cin >> l;
	for (int i = 0; i < l; ++i) {
		cin >> time >> direction;
		directions.push({ time + 1, direction });
	}
	snake.push_back({ 1,1 });
	map[1][1] = 1;
	int d = 1;
	int sec = 0;
	while(true) {
		++sec;
		if (!directions.empty() && directions.front().first == sec) {
			if (directions.front().second == 'L') d = (d + 3) % 4;
			else d = (d + 1) % 4;
			directions.pop();
		}
		pair<int, int> head = snake.front();
		snake.push_front({head.first + coords[d].first, head.second + coords[d].second});
		head = snake.front();
		if (map[head.first][head.second] == 1) break;
		if (map[head.first][head.second] != 2) {
			map[snake.back().first][snake.back().second] = 0;
			snake.pop_back();
		}
		map[head.first][head.second] = 1;
	}
	cout << sec << endl;
	return 0;
}