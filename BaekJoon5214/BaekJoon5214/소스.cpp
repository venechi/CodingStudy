#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	cin.tie(0);
	int n, k, m;
	cin >> n >> k >> m;
	vector<vector<int>> tubeNs(n);//i번째 역에서 접근 가능한 하이퍼튜브 번호 리스트
	vector<vector<int>> tubeInfos(m, vector<int>(k));//i번째 하이퍼튜브가 연결하는 역 리스트
	for (int i = 0; i < m; ++i) {//초기화
		for (int j = 0; j < k; ++j) {
			cin >> tubeInfos[i][j];
			--tubeInfos[i][j];
			tubeNs[tubeInfos[i][j]].push_back(i);
		}
	}
	if (n == 1) {//역이 하나인 경우
		cout << 1 << endl;
		return 0;
	}
	if (tubeNs[n - 1].size() == 0) {//마지막 역을 연결해주는 하이퍼튜브가 없는 경우
		cout << -1 << endl;
		return 0;
	}
	queue<pair<int, int>> q;
	q.push({ 0,1 });
	vector<bool> visited(n, false);
	visited[0] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (vector<int>::iterator it = tubeNs[cur.first].begin(); it != tubeNs[cur.first].end(); ++it) {
			if (tubeInfos[*it][0] == -1) continue;//최단거리를 구할 때, 한번 이용된 하이퍼튜브는 다시 이용될 일 없음.(이전 이용시에 가능한 모든 역을 방문 시도했기 때문)
			for (vector<int>::iterator it2 = tubeInfos[*it].begin(); it2 != tubeInfos[*it].end(); ++it2) {
				if (!visited[*it2]) {
					if (*it2 == n - 1) {
						cout << cur.second + 1 << endl;
						return 0;
					}
					visited[*it2] = true;
					q.push({ *it2, cur.second + 1 });
				}
			}
			tubeInfos[*it][0] = -1;//사용된 하이퍼튜브임을 나타내주기 위한 행위
		}
	}
	cout << -1 << endl;
	return 0;
}