#include <iostream>
#include <vector>

using namespace std;

int n, m, t;

vector<pair<int, int>> coords = {
	{0,1},{1,0}
};

vector<vector<int>> wheels;

void turn(int x, int d, int k) {
	for (int i = 0; i < n; ++i) {
		if ((i + 1) % x == 0) {
			if (d == 0) {
				for (int j = 0; j < k; ++j) {
					wheels[i].emplace(wheels[i].begin(), wheels[i].back());
					wheels[i].pop_back();
				}
			}
			else {
				for (int j = 0; j < k; ++j) {
					wheels[i].push_back(wheels[i][0]);
					wheels[i].erase(wheels[i].begin());
				}
			}
		}
	}
	vector<pair<int, int>> toErase;
	int sum = 0, cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (wheels[i][j] != 0) {
				++cnt;
				sum += wheels[i][j];
				bool erased = false;
				for (int k = 0; k < coords.size(); ++k) {
					int calX = i + coords[k].first, calY = (j + coords[k].second + m) % m;
					if (calX < 0 || calX >= n) continue;
					if (wheels[i][j] == wheels[calX][calY]) {
						toErase.push_back({ calX,calY });
						erased = true;
					}
				}
				if (erased) toErase.push_back({ i,j });
			}
		}
	}
	for (int i = 0; i < toErase.size(); ++i) wheels[toErase[i].first][toErase[i].second] = 0;
	if (toErase.size() == 0 && cnt != 0) {
		double avg = (double)sum / cnt;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (wheels[i][j] != 0) {
					if (avg > wheels[i][j]) ++wheels[i][j];
					else if (avg < wheels[i][j]) --wheels[i][j];
				}
			}
		}
	}
}

int getSum() {
	int sum = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)sum += wheels[i][j];
	return sum;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> m >> t;
	wheels = vector<vector<int>>(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> wheels[i][j];
	int x, d, k;
	for (int i = 0; i < t; ++i) {
		cin >> x >> d >> k;
		turn(x, d, k);
	}
	cout << getSum() << endl;
	return 0;
}