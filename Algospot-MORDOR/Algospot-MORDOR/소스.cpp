#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int n;
vector<int> height;
vector<int> maxHeight;
vector<int> minHeight;

int getValue(const vector<int>& target, int t_left, int t_right, int node, int left, int right, bool toMax) {
	if (t_left <= left && t_right >= right) return target[node];
	if (t_left > right || t_right < left) return toMax ? INT_MIN : INT_MAX;
	int mid = (left + right) / 2;
	left = getValue(target, t_left, t_right, node * 2 + 1, left, mid, toMax);
	right = getValue(target, t_left, t_right, node * 2 + 2, mid + 1, right, toMax);
	return toMax ? max(left, right) : min(left, right);
}

int getDifficulty(int left, int right) {
	return getValue(maxHeight, left, right, 0, 0, n - 1, true) - getValue(minHeight, left, right, 0, 0, n - 1, false);
}

int init(vector<int>& target, int left, int right, int node, bool toMax) {
	if (left == right) return target[node] = height[left];
	else {
		int mid = (left + right) / 2;
		left = init(target, left, mid, node * 2 + 1, toMax);
		right = init(target, mid + 1, right, node * 2 + 2, toMax);
		return target[node] = (toMax ? max(left, right) : min(left, right));
	}
}

void preCalc() {
	int treeSize = 1;
	while (treeSize < n) treeSize <<= 1;
	treeSize <<= 1;
	maxHeight = vector<int>(treeSize);
	minHeight = vector<int>(treeSize);
	init(minHeight, 0, n - 1, 0, false);
	init(maxHeight, 0, n - 1, 0, true);
}

int main(void) {
	ios::sync_with_stdio(false);
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int q, a, b;
		cin >> n >> q;
		height = vector<int>(n);
		for (int i = 0; i < n; ++i) cin >> height[i];
		preCalc();
		for (int i = 0; i < q; ++i) {
			cin >> a >> b;
			cout << getDifficulty(a, b) << "\n";
		}
	}
	return 0;
}