#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>


using namespace std;

int n;
vector<pair<double, double>> posts;
vector<vector<double>> distance_cache;

double getDistance(int from, int to) {
	double& ret = distance_cache[from][to];
	if (ret != -1) return ret;
	ret = sqrt(pow(posts[from].first - posts[to].first, 2) + pow(posts[from].second - posts[to].second, 2));
	distance_cache[to][from] = ret;
	return ret;
}

bool check(double distance) {
	bool* visited = new bool[n];
	memset(visited, 0, n * sizeof(bool));
	bool answer = true;
	queue<int> q;
	q.push(0);
	visited[0] = true;
	int current;
	while (!q.empty()) {
		current = q.front(); q.pop();
		for (int i = 0; i < n; ++i) {
			if (!visited[i] && getDistance(current, i) <= distance) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			answer = false;
			break;
		}
	}
	delete[]visited;
	return answer;
}

double calc() {
	double low = 0;
	double high = 1415;
	double mid;
	for (int i = 0; abs(high - low) > 0.0001; ++i) {
		mid = (low + high) / 2;
		if (check(mid))high = mid;
		else low = mid;
	}
	return low;
}

int main(void) {
	int tc;
	double x, y;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cin >> n;
		posts = vector<pair<double,double>>(n);
		distance_cache = vector<vector<double>>(n, vector<double>(n, -1));
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			posts[i] = { x, y };
		}
		printf_s("%0.2f\n", calc());
	}
	return 0;
}