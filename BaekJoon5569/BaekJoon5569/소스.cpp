#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 100000;


int main(void) {
	int w, h;
	cin >> w >> h;
	//w,h,d,available
	//d 1:north 0:east
	vector<vector<vector<vector<int>>>> map(w, vector<vector<vector<int>>>(h, vector<vector<int>>(2, vector<int>(2, 0))));
	for (int i = 0; i < w; ++i) {
		map[i][0][0][1] = 1;
	}
	for (int j = 0; j < h; ++j) {
		map[0][j][1][1] = 1;
	}
	for (int i = 1; i < w; ++i) {
		for (int j = 1; j < h; ++j) {
			//east a			//east na + east a
			map[i][j][0][1] = (map[i-1][j][0][0] + map[i-1][j][0][1]) % MOD;
			//north a           //north na + north a
			map[i][j][1][1] = (map[i][j-1][1][0] + map[i][j-1][1][1]) % MOD;
			//east na           //north a
			map[i][j][0][0] = map[i-1][j][1][1];
			//north na          //east a
			map[i][j][1][0] = map[i][j-1][0][1];
		}
	}
	int cnt = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cnt = (cnt + map[w - 1][h - 1][i][j]) % MOD;
		}
	}
	cout << cnt << endl;
	return 0;
}