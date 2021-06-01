#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> boggle(5);
vector<vector<vector<char>>> cache;
string toFind;

bool check(int x, int y, int left) {
	if (left == 0) return true;
	if (x == -1 || x == 5 || y == -1 || y == 5) return false;
	char& c = cache[x][y][left - 1];
	if (c != -1) return c == 0 ? false : true;
	if (toFind.at(toFind.length() - left) == boggle[x][y]) {
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0) continue;
				else {
					if (check(x + i, y + j, left - 1)) {
						c = 1;
						return true;
					}
				}
			}
		}
	}
	c = 0;
	return false;
}

bool isAvailable() {
	cache = vector<vector<vector<char>>>(5, vector<vector<char>>(5, vector<char>(toFind.length(), -1)));
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (check(i, j, toFind.length())) return true;
		}
	}
	return false;
}

int main(void) {
	int tc, n;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		for (int i = 0; i < 5; ++i) {
			cin >> boggle[i];
		}
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> toFind;
			cout << toFind << (isAvailable() ? " YES\n" : " NO\n");
		}
	}
	return 0;
}