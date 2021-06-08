#include <iostream>
#include <vector>

using namespace std;

class disjointSet {
private:
	vector<int> parent;
	vector<int> size;
	vector<int> rank;
	vector<int> enemy;

	int find(int u) {
		if (u != parent[u]) parent[u] = find(parent[u]);
		return parent[u];
	}

	int merge(int u, int v) {
		if (u == -1 || v == -1) return max(u, v);
		u = find(u); v = find(v);
		if (u == v) return u;
		if (rank[u] == rank[v]) rank[u]++;
		else if (rank[u] < rank[v]) {
			int temp = u; u = v; v = temp;
		}
		parent[v] = u;
		size[u] += size[v];
		return u;
	}

public:
	disjointSet(int n) :parent(n), size(n, 1), enemy(n, -1), rank(n, 0) {
		for (int i = 0; i < n; ++i) parent[i] = i;
	}

	bool ack(int u, int v) {
		u = find(u); v = find(v);
		if (enemy[u] == v) return false;
		int a = merge(u, v);
		int b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		if(b != -1) enemy[b] = a;
		return true;
	}

	bool dis(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return false;
		int a = merge(u, enemy[v]);
		int b = merge(v, enemy[u]);
		enemy[a] = b;
		enemy[b] = a;
		return true;
	}

	int getMaxPartySize() {
		int cnt = enemy.size();
		for (int i = 0; i < enemy.size(); ++i) {
			if (i == parent[i] && enemy[i] != -1 && enemy[i] > enemy[enemy[i]]) {
				cnt -= min(size[enemy[i]], size[enemy[enemy[i]]]);
			}
		}
		return cnt;
	}
};

int main(void) {
	int tc, n, m, a, b;
	string input;
	ios::sync_with_stdio(false);
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cin >> n >> m;
		disjointSet set(n);
		bool contradiction = false;
		for (int i = 0; i < m; ++i) {
			cin >> input >> a >> b;
			if (contradiction) continue;
			
			if (input == "ACK") contradiction = !(set.ack(a, b));
			else contradiction = !(set.dis(a, b));

			if(contradiction) cout << "CONTRADICTION AT " << i + 1 << endl;
		}
		if (!contradiction) {
			cout << "MAX PARTY SIZE IS " << set.getMaxPartySize() << endl;
		}
	}
	return 0;
}