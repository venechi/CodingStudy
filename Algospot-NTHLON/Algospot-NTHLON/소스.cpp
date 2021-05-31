#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

int main(void) {
	int testcase, m, a, b, nextNode;
	cin >> testcase;
	do {
		cin >> m;
		map<int, int> times;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			if (times.find(a - b) != times.end())
				times[a - b] = min(a, times[a - b]);
			else
				times[a - b] = a;
		}
		bool start = true, found = false;
		pair<int, int> current;
		//우선순위 큐를 이용해 경과시간이 가장 작은 경기조합을 우선 탐색
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
		vector<bool> visited(399, false);
		//총 걸린시간, a선수와 b선수의 시간차이
		Q.push({ 0,0 });
		while (!Q.empty()) {
			current = Q.top();
			Q.pop();
			//이전에 이미 최소시간이 결정되었으면 무시
			if (visited[current.second + 199])
				continue;
			//아니면 이번에 결정
			else
				visited[current.second + 199] = true;
			//경기를 하나는 해야 하므로 최초 0은 무시
			if (current.second == 0) {
				if (start) {
					start = false;
					visited[199] = false;
				}
				//시간차가 0이 되는 순간 경과시간이 최소가 되는 경기조합이 결정됨
				else {
					cout << current.first << "\n";
					found = true;
					break;
				}
			}
			for (const pair<int,int>& it : times) {
				nextNode = current.second + it.first;
				//시간차가 -199분에서 199분 사이이고 그 시간차를 갖는 경기 조합이 이전에 발견되지 않았으면 Q에 삽입
				if (nextNode <= 199 && nextNode >= -199 && !visited[nextNode + 199]) {
					Q.push({ current.first + it.second ,nextNode });
				}
			}
		}
		if (!found) cout << "IMPOSSIBLE\n";
	} while (--testcase);
	return 0;
}