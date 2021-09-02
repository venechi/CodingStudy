#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> in;
vector<vector<int>> graph;

vector<int> topologicalSort() {
	vector<int> ans;
	queue<int> q;
	for (int i = 0; i < in.size(); ++i) if (in[i] == 0) q.push(i);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		ans.push_back(cur + 1);
		for (int j : graph[cur]) {
			--in[j];
			if (in[j] == 0) q.push(j);
		}
	}
	return ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	in = vector<int>(n, 0);
	graph = vector<vector<int>>(n);
	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		--a; --b;
		++in[b];
		graph[a].push_back(b);
	}
	vector<int> ans = topologicalSort();
	for (int a : ans) cout << a << " ";
	return 0;
}