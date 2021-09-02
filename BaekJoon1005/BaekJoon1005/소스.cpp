#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> timeNeeded;
vector<int> in;
vector<vector<int>> graph;

class cmp {
public:
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[2] > b[2];
	}
};

int getMinTime(int w) {
	int sec = 0;
	//건물번호, 시작시간, 종료시간
	priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
	for (int i = 0; i < in.size(); ++i) if (in[i] == 0) pq.push({ i,0,timeNeeded[i] });
	while (!pq.empty()) {
		vector<int> cur = pq.top(); pq.pop();
		if (cur[0] == w) return cur[2];
		sec = cur[2];
		for (int i : graph[cur[0]]) {
			--in[i];
			if (in[i] == 0) {
				pq.push({ i, sec, sec + timeNeeded[i] });
			}
		}
	}
	return -1;
}

int main(void) {
	ios::sync_with_stdio(false);
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int n, k, x, y, w;
		cin >> n >> k;
		timeNeeded = vector<int>(n);
		in = vector<int>(n);
		graph = vector<vector<int>>(n);
		for (int j = 0; j < n; ++j)cin >> timeNeeded[j];
		for (int j = 0; j < k; ++j) {
			cin >> x >> y;
			--x; --y;
			++in[y];
			graph[x].push_back(y);
		}
		cin >> w;
		cout << getMinTime(w - 1) << "\n";
	}
	return 0;
}