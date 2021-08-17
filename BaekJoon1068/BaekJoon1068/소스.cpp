#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<int>> tree(n);
	vector<int> parent(n);
	int root;
	for (int i = 0; i < n; ++i) {
		cin >> parent[i];
		if (parent[i] == -1) {
			root = i;
		}
		else {
			tree[parent[i]].push_back(i);
		}
	}
	int toDelete;
	cin >> toDelete;
	if (parent[toDelete] == -1) cout << 0;
	else {
		int pos;
		for (int i = 0; i < tree[parent[toDelete]].size(); ++i) {
			if (tree[parent[toDelete]][i] == toDelete) {
				pos = i;
				break;
			}
		}
		tree[parent[toDelete]].erase(tree[parent[toDelete]].begin() + pos);
		queue<int> q;
		q.push(root);
		int cnt = 0;
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			if (tree[cur].size() == 0) ++cnt;
			else {
				for (int i = 0; i < tree[cur].size(); ++i) {
					q.push(tree[cur][i]);
				}
			}
		}
		cout << cnt;
	}
	return 0;
}