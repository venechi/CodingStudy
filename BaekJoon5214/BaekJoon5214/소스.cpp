#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	cin.tie(0);
	int n, k, m;
	cin >> n >> k >> m;
	vector<vector<int>> tubeNs(n);//i��° ������ ���� ������ ������Ʃ�� ��ȣ ����Ʈ
	vector<vector<int>> tubeInfos(m, vector<int>(k));//i��° ������Ʃ�갡 �����ϴ� �� ����Ʈ
	for (int i = 0; i < m; ++i) {//�ʱ�ȭ
		for (int j = 0; j < k; ++j) {
			cin >> tubeInfos[i][j];
			--tubeInfos[i][j];
			tubeNs[tubeInfos[i][j]].push_back(i);
		}
	}
	if (n == 1) {//���� �ϳ��� ���
		cout << 1 << endl;
		return 0;
	}
	if (tubeNs[n - 1].size() == 0) {//������ ���� �������ִ� ������Ʃ�갡 ���� ���
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
			if (tubeInfos[*it][0] == -1) continue;//�ִܰŸ��� ���� ��, �ѹ� �̿�� ������Ʃ��� �ٽ� �̿�� �� ����.(���� �̿�ÿ� ������ ��� ���� �湮 �õ��߱� ����)
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
			tubeInfos[*it][0] = -1;//���� ������Ʃ������ ��Ÿ���ֱ� ���� ����
		}
	}
	cout << -1 << endl;
	return 0;
}