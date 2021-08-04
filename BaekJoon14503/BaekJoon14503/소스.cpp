#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> coords = {
	{-1,0},{0,1},{1,0},{0,-1} 
};

int main(void) {
	ios::sync_with_stdio(false);
	int n, m, x, y, d;
	cin >> n >> m >> x >> y >> d;
	vector<vector<int>> map(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i)for (int j = 0; j < m; ++j)cin >> map[i][j];
	//d=> 0:north 1:east 2:south 3:west
	int cnt = 0;
	while (true) {
		if (map[x][y] == 0) {
			map[x][y] = 2;
			++cnt;
		}
		if (map[x][y] == 1) break;
		pair<int, int> next = coords[(d + 2) % 4];
		for (int i = 0; i < coords.size(); ++i) {
			d = (d + 3) % 4;
			if (map[x + coords[d].first][y + coords[d].second] == 0) {
				next = coords[d];
				break;
			}
		}
		x += next.first;
		y += next.second;
	}
	cout << cnt << endl;
	return 0;
}