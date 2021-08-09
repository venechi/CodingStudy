#include <iostream>
#include <vector>

using namespace std;

vector<int> parents;
//��ξ��ට���� ��� ��Ȯ�� ���� �ƴ����� ���� �̾��� ���� ����� ���� �߰�
//�� �ڵ�� ���� �ν��к��� ��� �̵��� ū���� ��� �ʿ�.
//cin.tie(0)�� ���ؼ� �ڲ� �ð��ʰ��� ���� ��Ե� ����ð��� �ٿ������� ����̾���.
vector<int> height;

int findParent(int target) {
	if (parents[target] == -1) return target;
	else return parents[target] = findParent(parents[target]);
}

void join(int a, int b) {
	if (findParent(a) != findParent(b)) {
		if (height[findParent(a)] > height[findParent(b)]) {
			parents[findParent(b)] = findParent(a);
		}
		else if (height[findParent(a)] > height[findParent(b)]) {
			parents[findParent(a)] = findParent(b);
		}
		else {
			parents[findParent(a)] = findParent(b);
			height[findParent(b)]++;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	parents = vector<int>(n + 1, -1);
	height = vector<int>(n + 1, 0);
	int ins, a, b;
	for (int i = 0; i < m; ++i) {
		cin >> ins >> a >> b;
		if (ins == 0) {
			join(a, b);
		}
		else {
			if (findParent(a) == findParent(b)) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}