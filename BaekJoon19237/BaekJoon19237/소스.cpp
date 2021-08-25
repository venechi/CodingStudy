#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> coords = {
	{-1,0}, {1,0},{0,-1},{0,1}
};

int n, m, k;
				//#shark, remainingTime
vector<vector<pair<int, int>>> map;
vector<vector<vector<int>>> priority;
//direction, x, y
vector<vector<int>> sharks;

void removeTracks() {
	for (int i = 0; i < m; ++i) {
		if(sharks[i][0] != -1)
			++map[sharks[i][1]][sharks[i][2]].second;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j].first != 0) {
				--map[i][j].second;
				if (map[i][j].second == 0)
					map[i][j].first = 0;
			}
		}
	}
}

bool move() {
	int sharkCnt = 0;
	for (int i = 0; i < m; ++i) {
		if (sharks[i][0] != -1) {
			++sharkCnt;
			//이동
			vector<int> keep = { -1 };
			bool went = false;
			for (int j = 0; j < 4; ++j) {
				int d = priority[i][sharks[i][0]][j];
				int calX = sharks[i][1] + coords[d].first;
				int calY = sharks[i][2] + coords[d].second;
				if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
				if (map[calX][calY].first == 0) {
					went = true;
					sharks[i] = { d, calX, calY };
					break;
				}
				if (map[calX][calY].first == i + 1 && keep[0] == -1) keep = { d,calX,calY };
			}
			if (!went && keep[0] != -1) {
				sharks[i] = keep;
			}
		}
	}
	//지도에 적용 및 상어 추방
	for (int i = 0; i < m; ++i) {
		if (sharks[i][0] != -1) {
			pair<int, int>& onTheMap = map[sharks[i][1]][sharks[i][2]];
			if (onTheMap.first == 0 || sharks[onTheMap.first - 1][0] == -1 || onTheMap.first == i + 1) onTheMap = { i + 1, k };
			else {
				if (sharks[onTheMap.first - 1][1] == sharks[i][1] && sharks[onTheMap.first - 1][2] == sharks[i][2]) {
					--sharkCnt;
					if (onTheMap.first < i + 1) {
						sharks[i][0] = -1;
					}
					else {
						sharks[onTheMap.first - 1][0] = -1;
						onTheMap.first = i + 1;
					}
				}
			}
		}
	}
	if (sharkCnt == 1) return true;
	removeTracks();
	return false;
}

int main(void) {
	cin >> n >> m >> k;
	map = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(n));
	sharks = vector<vector<int>>(m, vector<int>());
	priority = vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(4)));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> map[i][j].first;
			if (map[i][j].first == 0) map[i][j].second = 0;
			else {
				map[i][j].second = k;
				sharks[map[i][j].first - 1] = { 0,i,j };
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		cin >> sharks[i][0];
		--sharks[i][0];
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				cin >> priority[i][j][k];
				--priority[i][j][k];
			}
		}
	}
	bool gotcha = false;
	for (int sec = 1; sec <= 1000; ++sec) {
		gotcha = move();
		if (gotcha) {
			cout << sec;
			break;
		}
	}
	if(!gotcha) cout << -1;
	return 0;
}