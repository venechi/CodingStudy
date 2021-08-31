#include <iostream>
#include <vector>

using namespace std;

class segTree {
private:
	vector<int> tree;
	vector<int> origin;
	int (*cmp)(int, int);
	int defaultValue;

	int init(int nodeNum, int left, int right) {
		if (left == right) return tree[nodeNum] = origin[left];
		else {
			int mid = (left + right) / 2;
			return tree[nodeNum] = cmp(init(nodeNum * 2, left, mid), init(nodeNum * 2 + 1, mid + 1, right));
		}
	}

	int query(int left, int right,int nodeNum, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || left > nodeRight) return defaultValue;
		if (nodeRight <= right && nodeLeft >= left) return tree[nodeNum];
		int mid = (nodeLeft + nodeRight) / 2;
		int leftValue = query(left, right, nodeNum * 2, nodeLeft, mid), rightValue = query(left, right, nodeNum * 2 + 1, mid + 1, nodeRight);
		return cmp(leftValue, rightValue);
	}
public:
	segTree(vector<int> n, int (*cmp)(int,int)) {
		origin = n;
		tree = vector<int>(4 * origin.size());
		this->cmp = cmp;
		init(1, 0, origin.size() - 1);
		defaultValue = cmp(-1, 1234567890) == -1 ? 1234567890 : -1;
	}

	int getValue(int left, int right) {
		return query(left, right, 1, 0, origin.size() - 1);
	}
};

int getMin(int a, int b) {
	return min(a, b);
}

int getMax(int a, int b) {
	return max(a, b);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, a, b;
	cin >> n >> m;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) cin >> arr[i];
	segTree mini(arr, getMin);
	segTree maxi(arr, getMax);
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		--a; --b;
		cout << mini.getValue(a, b) << " " << maxi.getValue(a, b) << "\n";
	}
	return 0;
}