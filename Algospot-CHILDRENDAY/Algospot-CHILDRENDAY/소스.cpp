#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int append(int current, int edge, int mod) {
	current = current * 10 + edge;
	if (current >= mod)
		return mod + (current % mod);
	else return current;
}

int main(void) {
	int testcase, m, n, current, next;
	string numbers;
	queue<int> Q;
	cin >> testcase;
	for (int i = 0; i < testcase; ++i) {
		cin >> numbers >> n >> m;
		//������ ���� ���� ���� �����ϱ� ���ؼ� �̿밡���� ���ڸ� ������������ �����Ѵ�.
		sort(numbers.begin(), numbers.end());
		//(0 ~ n-1)������ ��ü ���� m+n ������ ���, (n ~ 2n-1)������ ��ü ���� m+n �̻��� ��쿡 ���
		vector<int> parent(2 * n, -1), choice(2 * n, -1);
		parent[0] = 0;
		Q.push(0);
		while (!Q.empty()) {
			current = Q.front();
			Q.pop();
			for (int i = 0; i < numbers.size(); ++i) {
				//���� ��忡�� ��� ������ ������ �� ������ ���� ��带 ����
				next = append(current, int(numbers[i] - '0'), n);
				//������ ������ �� ���°��
				//������ ������ ���� ���� ������ ��찡 �ּҰ��̹Ƿ� ������Ʈ ���� �ʴ´�.
				if (parent[next] == -1) {
					//next�� �������´� current;
					parent[next] = current;
					//current���� � ���ڸ� �߰��ߴ��� ���� ���
					//mod���갪�� �̿��ϹǷ� �� ������ ���̴� �������·� �����ϰ� ���ƿ� �� ����.
					choice[next] = int(numbers[i] - '0');
					//��ǥ�� ������ ��� ���� Ż��
					if (next == n + m) {
						while (!Q.empty()) Q.pop();
						break;
					}
					//�߰� Ž���� ���� ť�� ����
					else
						Q.push(next);
				}
			}
		}
		if (parent[n + m] == -1)cout << "IMPOSSIBLE\n";
		else {
			string answer = "";
			current = m + n;
			while (parent[current] != current) {
				answer += char(choice[current] + '0');
				current = parent[current];
			}
			reverse(answer.begin(), answer.end());
			cout << answer << "\n";
		}
	}
	return 0;
}