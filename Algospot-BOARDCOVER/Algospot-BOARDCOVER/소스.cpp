#include <iostream>
#include <vector>

using namespace std;

int h, w;

vector<vector<pair<int, int>>> directions = { {{0,0},{1,0},{1,1}},{{0,0},{0,1},{1,0}},{{0,0},{1,1},{0,1}},{{0,0},{1,0},{1,-1}} };

bool isEmpty(const vector<vector<bool>>& map, const vector<pair<int, int>>& target, int x, int y) {
	int calX, calY;
	for (int i = 0; i < target.size(); ++i) {
		calX = x + target[i].first;
		calY = y + target[i].second;
		if (calX < 0 || calX >= h || calY < 0 || calY >= w) return false;
		if (map[calX][calY]) return false;
	}
	return true;
}

void toggleSet(vector<vector<bool>>& map, const vector<pair<int, int>>& target, int x, int y) {
	int calX, calY;
	for (int i = 0; i < target.size(); ++i) {
		calX = x + target[i].first;
		calY = y + target[i].second;
		map[calX][calY] = !map[calX][calY];
	}
}

int calc(vector<vector<bool>> map) {
	int x = -1, y = -1, cnt = 0;
	for (int i = 0; i < h && x == -1; ++i) {
		for (int j = 0; j < w; ++j) {
			if (!map[i][j]) {
				x = i;
				y = j;
				break;
			}
		}
	}
	if (x == -1) return 1;
	for (int i = 0; i < directions.size(); ++i) {
		if (isEmpty(map, directions[i], x, y)) {
			toggleSet(map, directions[i], x, y);
			cnt += calc(map);
			toggleSet(map, directions[i], x, y);
		}
	}
	return cnt;
}

int main(void) {
	int tc;
	char input;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int cnt = 0;
		cin >> h >> w;
		vector<vector<bool>> map(h, vector<bool>(w, false));
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cin >> input;
				if (input == '#') map[i][j] = true;
				else ++cnt;
			}
		}
		if (cnt % 3 != 0) cout << 0 << endl;
		else cout << calc(map) << endl;
	}
	return 0;
}