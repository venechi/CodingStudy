#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<int>> tree(n);
	int a, b;
	for (int i = 0; i < n - 1; ++i) {
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}
	vector<int> parents(n, -1);
	parents[0] = 0;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int i = 0; i < tree[cur].size(); ++i) {
			if (parents[tree[cur][i]] == -1) {
				parents[tree[cur][i]] = cur;
				q.push(tree[cur][i]);
			}
		}
	}
	for (int i = 1; i < n; ++i) cout << parents[i] + 1 << "\n";
	return 0;
}