#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> map(101, vector<bool>(101, false));

vector<pair<int, int>> coords = {
	{1,0},{0,-1},{-1,0},{0,1}
};

								//x,y,d,g  //true:left, false:right
vector<int> dragonC(vector<int> info, bool curve) {
	if (info[3] == 0) {
		int calX = info[0] + coords[info[2]].first, calY = info[1] + coords[info[2]].second;
		map[info[0]][info[1]] = true;
		map[calX][calY] = true;
		return { calX,calY,info[2] };
	}
	else {
		vector<int> last = dragonC({ info[0],info[1],info[2],info[3] - 1 }, true);
		last[2] = (last[2] + (curve ? 1 : 3)) % 4;
		last.push_back(info[3] - 1);
		return dragonC(last, false);
	}
}

int cntSquare() {
	int cnt = 0;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1]) ++cnt;
		}
	}
	return cnt;
}

int main(void) {
	int n;
	cin >> n;
	vector<int> input(4);
	for (int i = 0; i < n; ++i) {
		cin >> input[0] >> input[1] >> input[2] >> input[3];
		dragonC(input, true);
	}
	cout << cntSquare() << endl;
}