#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class cmp {
public:
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[0] > b[0];
	}
};

vector<int> group;

int getGroup(int a) {
	if (group[a] == -1) return a;
	else return group[a] = getGroup(group[a]);
}

bool makeGroup(int a, int b) {
	int aGroup = getGroup(a);
	int bGroup = getGroup(b);
	if (aGroup == bGroup) return false;
	group[aGroup] = bGroup;
	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	int n, m, a, b, c;
	cin >> n >> m;
	group = vector<int>(n + 1, -1);
	priority_queue<vector<int>, vector<vector<int>>, cmp> q;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		q.push({ c, a, b });
	}
	int score = 0;
	while (!q.empty()) {
		vector<int> cur = q.top(); q.pop();
		if (makeGroup(cur[1], cur[2])) {
			score += cur[0];
		}
	}
	cout << score;
	return 0;
}