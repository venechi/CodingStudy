#include <iostream>
#include <vector>

using namespace std;

int n;

vector<vector<vector<vector<int>>>> fireballs;

vector<pair<int, int>> coords = {
	{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
};

void move() {
	vector<vector<vector<vector<int>>>> after(n, vector<vector<vector<int>>>(n, vector<vector<int>>()));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			vector<vector<int>>& cur = fireballs[i][j];
			for (int k = 0; k < cur.size(); ++k) {
				int calX = i + (coords[cur[k][2]].first * cur[k][1]), calY = j + (coords[cur[k][2]].second * cur[k][1]);
				calX = (calX + n * 250) % n;
				calY = (calY + n * 250) % n;
				after[calX][calY].push_back(cur[k]);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (after[i][j].size() >= 2) {
				vector<vector<int>>& cur = after[i][j];
				int weightSum = cur[0][0], speedSum = cur[0][1];
				bool prevIsEven = (cur[0][2] % 2 == 0);
				bool allEvenOrOdd = true;
				for (int i = 1; i < cur.size(); ++i) {
					weightSum += cur[i][0];
					speedSum += cur[i][1];
					if ((cur[i][2] % 2 == 0) != prevIsEven) {
						allEvenOrOdd = false;
					}
				}
				weightSum /= 5;
				speedSum /= cur.size();
				cur.clear();
				if (weightSum != 0) {
					for (int i = 0; i < 4; ++i) {
						cur.push_back({ weightSum, speedSum, (allEvenOrOdd ? 0 : 1) + i * 2 });
					}
				}
			}
		}
	}
	fireballs = after;
}

int sumOfFireballWeights() {
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < fireballs[i][j].size(); ++k) {
				sum += fireballs[i][j][k][0];
			}
		}
	}
	return sum;
}

int main(void) {
	ios::sync_with_stdio(false);
	int m, k, x, y, w, s, d;
	cin >> n >> m >> k;
	fireballs = vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(n, vector<vector<int>>()));
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> w >> s >> d;
		fireballs[x - 1][y - 1].push_back({ w,s,d });
	}
	for (int i = 0; i < k; ++i) move();
	cout << sumOfFireballWeights() << endl;
	return 0;
}