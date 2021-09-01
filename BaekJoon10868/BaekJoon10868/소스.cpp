#include <iostream>
#include <vector>

using namespace std;

class segTree {
private:
	int n;
	vector<int> tree;

	int init(const vector<int>& origin, int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeLeft + 1 == nodeRight) return tree[nodeNum] = origin[nodeLeft];
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return tree[nodeNum] = min(init(origin, nodeNum * 2, nodeLeft, mid), init(origin, nodeNum * 2 + 1, mid, nodeRight));
		}
	}

	int getValue(const int left, const int right, int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeRight <= left || right <= nodeLeft) return 1234567890;
		if (nodeLeft >= left && nodeRight <= right) return tree[nodeNum];
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return min(getValue(left, right, nodeNum * 2, nodeLeft, mid), getValue(left, right, nodeNum * 2 + 1, mid, nodeRight));
		}
	}
public:
	segTree(const vector<int>& arr) {
		n = arr.size();
		tree = vector<int>(4 * n, 0);
		init(arr, 1, 0, n);
	}

	int getRangeMinimum(int left, int right) {
		return getValue(left, right, 1, 0, n);
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, a, b;
	cin >> n >> m;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)cin >> arr[i];
	segTree t(arr);
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		cout << t.getRangeMinimum(a - 1, b) << "\n";
	}
	return 0;
}