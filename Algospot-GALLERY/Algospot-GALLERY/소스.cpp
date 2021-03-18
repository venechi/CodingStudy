#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map;
vector<bool> visited;
vector<int> status;

enum {
	//0b001
	UNWATCHED = 1,
	//0b010
	WATCHED = 2,
	//0b100
	INSTALLED = 4
};

//dfs�� �̿��Ѵ�
void check(int pos) {
	visited[pos] = true;
	for (int i = 0; i < map[pos].size(); ++i) {
		int next = map[pos][i];
		//�ڽĳ�
		if (!visited[next]) {
			check(next);
			//�ڽ��� ���õǰ� ���� ������
			if (status[next] & UNWATCHED) {
				//�θ� ī�޶� ��ġ
				status[pos] = (INSTALLED | WATCHED);
				//�ڽ� ���õ�
				status[next] = WATCHED;
			}
			//�ڽĿ��� ī�޶� ��ġ������
			else if (status[next] & INSTALLED) {
				//�θ� ���õ�
				//��Ʈ ���� �����ڴ� '~'�̴�. ('!'�ƴ� -> bool �����ڷ� true/false�� �ٲ����)
				status[pos] &= (~UNWATCHED);
				status[pos] |= WATCHED;
			}
		}
	}
}

int main(void) {
	int testcase;
	int g, h;
	int from, to;
	int count;
	cin >> testcase;
	for (int i = 0; i < testcase; ++i) {
		count = 0;
		cin >> g >> h;
		map = vector<vector<int>>(g, vector<int>());
		status = vector<int>(g, UNWATCHED);
		visited = vector<bool>(g, false);
		for (int i = 0; i < h; ++i) {
			cin >> from >> to;
			map[from].push_back(to);
			map[to].push_back(from);
		}
		//������ ��Ʈ���� Ʈ����� ���� ��õǾ� �����Ƿ�(�� �� ������ �������� �ٽ� ������ ���ؼ��� ���� ���� ������ �ݵ�� ������ ��),
		//Ʈ���� �������� �����Ͽ� ������ Ǯ �� �ִ�.
		for (int i = 0; i < g; ++i) {
			if (!visited[i]) check(i);
			//������Ʈ�� ������Ұ� 1���� ��� UNWATCHED�� ���������Ƿ� ī�޶� ��ġ�Ѵ�.
			if (status[i] & (INSTALLED | UNWATCHED)) ++count;
		}
		cout << count << "\n";
	}
	return 0;
}