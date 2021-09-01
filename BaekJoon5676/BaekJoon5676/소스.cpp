#include <iostream>
#include <vector>

using namespace std;

class segTree {
private:
	int n;
	vector<int> tree;
	
	int getValue(const int left, const int right, int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeRight <= left || right <= nodeLeft) return 1;
		if (left <= nodeLeft && nodeRight <= right) return tree[nodeNum];
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return getValue(left, right, nodeNum * 2, nodeLeft, mid) * getValue(left, right, nodeNum * 2 + 1, mid, nodeRight);
		}
	}

	int update(const int pos, const int value, int nodeNum, int nodeLeft, int nodeRight) {
		if (pos < nodeLeft || pos >= nodeRight) return tree[nodeNum];
		if (nodeLeft + 1 == nodeRight) return tree[nodeNum] = value;
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return tree[nodeNum] = update(pos, value, nodeNum * 2, nodeLeft, mid) * update(pos, value, nodeNum * 2 + 1, mid, nodeRight);
		}
	}

	int init(const vector<int>& origin, int nodeNum, int nodeLeft, int nodeRight) {
		if (nodeLeft + 1 == nodeRight) return tree[nodeNum] = origin[nodeLeft];
		else {
			int mid = (nodeLeft + nodeRight) / 2;
			return tree[nodeNum] = init(origin, nodeNum * 2, nodeLeft, mid) * init(origin, nodeNum * 2 + 1, mid, nodeRight);
		}
	}

	int convert(int value) {
		if (value != 0) {
			if (value < 0) return -1;
			else return 1;
		}
		else return 0;
	}
public:
	segTree(vector<int> arr) {
		tree = vector<int>(arr.size() * 4);
		for (int i = 0; i < arr.size(); ++i) arr[i] = convert(arr[i]);
		n = arr.size();
		init(arr, 1, 0, n);
	}

	void assign(int pos, int value) {
		update(pos - 1, convert(value), 1, 0, n);
	}

	char getRangeMul(int left, int right) {
		int ans = getValue(left - 1, right, 1, 0, n);
		if (ans != 0) {
			if (ans < 0) return '-';
			else return '+';
		}
		else return '0';
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	while (cin >> n >> k) {
		vector<int> arr(n);
		string ans = "";
		for (int i = 0; i < n; ++i) cin >> arr[i];
		segTree p(arr);
		char ins;
		int a, b;
		for (int i = 0; i < k; ++i) {
			cin >> ins >> a >> b;
			if (ins == 'C') p.assign(a, b);
			else ans += p.getRangeMul(a, b);
		}
		cout << ans << "\n";
	}
	return 0;
}