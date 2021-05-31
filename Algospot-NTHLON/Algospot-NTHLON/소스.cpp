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
		//�켱���� ť�� �̿��� ����ð��� ���� ���� ��������� �켱 Ž��
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
		vector<bool> visited(399, false);
		//�� �ɸ��ð�, a������ b������ �ð�����
		Q.push({ 0,0 });
		while (!Q.empty()) {
			current = Q.top();
			Q.pop();
			//������ �̹� �ּҽð��� �����Ǿ����� ����
			if (visited[current.second + 199])
				continue;
			//�ƴϸ� �̹��� ����
			else
				visited[current.second + 199] = true;
			//��⸦ �ϳ��� �ؾ� �ϹǷ� ���� 0�� ����
			if (current.second == 0) {
				if (start) {
					start = false;
					visited[199] = false;
				}
				//�ð����� 0�� �Ǵ� ���� ����ð��� �ּҰ� �Ǵ� ��������� ������
				else {
					cout << current.first << "\n";
					found = true;
					break;
				}
			}
			for (const pair<int,int>& it : times) {
				nextNode = current.second + it.first;
				//�ð����� -199�п��� 199�� �����̰� �� �ð����� ���� ��� ������ ������ �߰ߵ��� �ʾ����� Q�� ����
				if (nextNode <= 199 && nextNode >= -199 && !visited[nextNode + 199]) {
					Q.push({ current.first + it.second ,nextNode });
				}
			}
		}
		if (!found) cout << "IMPOSSIBLE\n";
	} while (--testcase);
	return 0;
}