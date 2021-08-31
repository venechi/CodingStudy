#include <iostream>
#include <vector>

using namespace std;

class segTree {
private:
	vector<int> tree;
	vector<int> origin;
	const int MOD = 1000000007;

	int init(int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeLeft == nodeRight - 1) return tree[nodeNum] = origin[nodeLeft];
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return tree[nodeNum] = ((long long)init(nodeNum * 2, nodeLeft, mid) * init(nodeNum * 2 + 1, mid, nodeRight)) % MOD;
		}
	}

	int set(const int pos, const int newValue, const int oldValue, int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeLeft <= pos && nodeRight > pos) {
			if (nodeLeft == nodeRight - 1) return tree[nodeNum] = newValue;
			else {
				int mid = (nodeLeft + nodeRight) / 2;
				return tree[nodeNum] = ((long long)set(pos, newValue, oldValue, nodeNum * 2, nodeLeft, mid) * set(pos, newValue, oldValue, nodeNum * 2 + 1, mid, nodeRight)) % MOD;
			}
		}
		else return tree[nodeNum];
	}

	int getValue(const int left, const int right, int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeLeft >= right || nodeRight <= left) return 1;
		if (left <= nodeLeft && right >= nodeRight) return tree[nodeNum];
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return ((long long)getValue(left, right, nodeNum * 2, nodeLeft, mid) * getValue(left, right, nodeNum * 2 + 1, mid, nodeRight)) % MOD;
		}
	}

public:
	segTree(const vector<int>& origin) {
		this->origin = origin;
		this->tree = vector<int>(origin.size() * 4, 0);
		init(1, 0, origin.size());
	}
	
	void update(int pos, int value) {
		set(pos, value, origin[pos], 1, 0, origin.size());
		origin[pos] = value;
	}

	int getRangeMul(int left, int right) {
		return getValue(left, right, 1, 0, origin.size());
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)cin >> arr[i];
	segTree t(arr);
	int a, b, c;
	for (int i = 0; i < m + k; ++i) {
		cin >> a >> b >> c;
		if (a == 1) t.update(--b, c);
		else cout << t.getRangeMul(--b, c) << "\n";
	}
	return 0;
}