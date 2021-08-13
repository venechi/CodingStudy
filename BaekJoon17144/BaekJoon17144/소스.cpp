#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> coords = {
	      {-1,0},
	{0,-1},     {0,1},
	       {1,0}
};

vector<vector<int>> map;
int U_AP = -1;
int D_AP = -1;

void spread() {
	vector<vector<int>> next(map.size(), vector<int>(map[0].size(), 0));
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			if (map[i][j] != 0) {
				int cnt = 0;
				for (int k = 0; k < coords.size(); ++k) {
					int calX = i + coords[k].first, calY = j + coords[k].second;
					if (calX < 0 || calX >= map.size() || calY < 0 || calY >= map[i].size())continue;
					if (calY == 0 && (calX == U_AP || calX == D_AP))continue;
					next[calX][calY] += map[i][j] / 5;
					++cnt;
				}
				next[i][j] += (map[i][j] - (map[i][j] / 5) * cnt);
			}
		}
	}
	map = next;
}

void purify() {
	//upperCycle
	for (int i = U_AP - 1; i >= 0; --i) {
		map[i + 1][0] = map[i][0];
	}
	map[U_AP][0] = 0;
	map[0].erase(map[0].begin());
	map[0].push_back(map[1].back());
	for (int i = 1; i < U_AP; ++i) {
		map[i].back() = map[i + 1].back();
	}
	map[U_AP].pop_back();
	map[U_AP].emplace(map[U_AP].begin(), 0);
	//lowerCycle
	for (int i = D_AP; i < map.size() - 1; ++i) {
		map[i][0] = map[i + 1][0];
	}
	map[D_AP][0] = 0;
	map.back().erase(map.back().begin());
	map.back().push_back(map[map.size() - 2].back());
	for (int i = map.size() - 2; i > D_AP; --i) {
		map[i].back() = map[i - 1].back();
	}
	map[D_AP].pop_back();
	map[D_AP].emplace(map[D_AP].begin(), 0);
}

int cntFindDust() {
	int cnt = 0;
	for (int i = 0; i < map.size(); ++i)for (int j = 0; j < map[i].size(); ++j) cnt += map[i][j];
	return cnt;
}

int main(void) {
	ios::sync_with_stdio(false);
	int r, c, t;
	cin >> r >> c >> t;
	map = vector<vector<int>>(r, vector<int>(c));
	for (int i = 0; i < r; ++i)for (int j = 0; j < c; ++j)cin >> map[i][j];
	for (int i = 0; i < r; ++i) {
		if (map[i][0] == -1) {
			if (U_AP == -1) U_AP = i;
			else D_AP = i;
			map[i][0] = 0;
		}
	}
	for (int i = 0; i < t; ++i) {
		spread();
		purify();
	}
	cout << cntFindDust() << endl;
	return 0;
}