#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> graph;

vector<int> d;

void dijkstra(int start) {
	d = vector<int>(graph.size(), 123456789);
	d[start] = 0;
	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int i = 0; i < graph[cur].size(); ++i) {
			if (graph[cur][i] != 123456 && d[cur] + graph[cur][i] < d[i]) {
				d[i] = d[cur] + graph[cur][i];
				q.push(i);
			}
		}
	}
}

int getMinimumDistance(int start, int end) {
	dijkstra(start);
	return d[end];
}

int main(void) {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	graph = vector<vector<int>>(n, vector<int>(n, 123456));
	int a, b, weight;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> weight;
		--a; --b;
		graph[a][b] = min(graph[a][b], weight);
	}
	cin >> a >> b;
	cout << getMinimumDistance(a - 1, b - 1);
	return 0;
}