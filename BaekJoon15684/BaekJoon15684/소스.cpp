#include <iostream>
#include <vector>

using namespace std;

int n, h;
vector < vector<pair<bool, bool>>> map;
vector<bool> touched;
int opt = 987654321;

int lineTracer(int line) {
	for (int i = 0; i < h; ++i) {
		if (map[line][i].first) --line;
		else if (map[line][i].second) ++line;
	}
	return line;
}

bool check() {
	for (int i = 0; i < n; ++i) {
		if (lineTracer(i) != i) return false;
	}
	return true;
}

bool addLine(int a, int b) {
	if (map[b][a].second || map[b][a].first || map[b + 1][a].second) return false;
	map[b][a].second = true;
	map[b + 1][a].first = true;
	return true;
}

void removeLine(int a, int b) {
	map[b][a].second = false;
	map[b + 1][a].first = false;
}

int rec_func(int a, int b, int cnt) {
	if (cnt > opt || cnt > 3) return 987654321;
	if (b == n - 1) {
		if (check()) return cnt;
		else return 987654321;
	}
	int nextA, nextB;
	if (a == h - 1) nextA = 0, nextB = b + 1;
	else nextA = a + 1, nextB = b;
	opt = min(opt, rec_func(nextA, nextB, cnt));
	if (touched[b] && addLine(a, b)) {
		opt = min(opt, rec_func(nextA, nextB, cnt + 1));
		removeLine(a, b);
	}
	return opt;
}

int main(void) {
	int m, a, b;
	cin >> n >> m >> h;
	map = vector<vector<pair<bool, bool>>>(n, vector<pair<bool, bool>>(h, { false,false }));
	touched = vector<bool>(n, false);
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		addLine(a - 1, b - 1);
		touched[b - 1] = true;;
	}
	int ans = rec_func(0, 0, 0);
	cout << (ans > 3 ? -1 : ans) << endl;
	return 0;
}