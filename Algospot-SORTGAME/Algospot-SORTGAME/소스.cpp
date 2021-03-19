#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_LENGTH = 8;
vector<int> original(MAX_LENGTH);
map<vector<int>, int> depth;

//2,1,0 �迭�� �����ϴµ� �ʿ��� ����
//2,1,0,3,4,5,6,7 �迭(2,1,0 ���Ĵ� ���ĵǾ�����)�� �����ϴµ� �ʿ��� ����� �����Ƿ�
//�Է� ������ �ִ� ������ �迭�� ���� ����� ����� ��
//�ִ� ���̺��� ª�� �迭�� �Է����� ������
//ª�� ���̸�ŭ ���ĵ� �迭�� �ڿ� �̾�ٿ��� �ʿ����� �����Ѵ�
//���� preCalc�� �ѹ��� ����ϸ� �ȴ�.
void preCalc() {
	vector<int> here = original;
	queue<vector<int>> Q;
	depth[here] = 0;
	Q.push(here);
	while (!Q.empty()) {
		here = Q.front();
		Q.pop();
		int cost = depth[here];
		for (int i = 0; i < MAX_LENGTH - 1; ++i) {
			for (int j = i + 2; j <= MAX_LENGTH; ++j) {
				reverse(here.begin() + i, here.begin() + j);
				if (depth.count(here) == 0) {
					depth[here] = cost + 1;
					Q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}

int main(void) {
	int testcase, n, cnt;
	cin >> testcase;
	for (int i = 0; i < MAX_LENGTH; ++i)
		original[i] = i;
	preCalc();
	do {
		cin >> n;
		vector<int> input(n);
		for (int i = 0; i < n; ++i) {
			cin >> input[i];
		}
		vector<int> processed = original;
		for (int i = 0; i < n; ++i) {
			cnt = 0;
			for (int j = 0; j < n; ++j)
				if (input[i] > input[j])++cnt;
			processed[i] = cnt;
		}
		cout << depth[processed] << "\n";
	} while (--testcase);
	return 0;
}