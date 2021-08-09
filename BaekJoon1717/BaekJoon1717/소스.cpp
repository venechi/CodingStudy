#include <iostream>
#include <vector>

using namespace std;

vector<int> parents;
//경로압축때문에 사실 정확한 값은 아니지만 아주 미약한 성능 향상을 위해 추가
//이 코드로 인한 로스분보다 얻는 이득이 큰지는 고민 필요.
//cin.tie(0)을 안해서 자꾸 시간초과가 떠서 어떻게든 수행시간을 줄여보려는 노력이었음.
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