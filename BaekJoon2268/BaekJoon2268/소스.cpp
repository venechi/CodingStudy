#include <iostream>
#include <vector>

using namespace std;

class penwick {
private:
	vector<int> origin;
	vector<long long> tree;

	void add(int pos, long long value) {
		while (pos < tree.size()) {
			tree[pos] += value;
			pos += (pos & -pos);
		}
	}

	long long pSum(int pos) {
		long long ans = 0;
		while (pos > 0) {
			ans += tree[pos];
			pos &= (pos - 1);
		}
		return ans;
	}

public:
	penwick(int n) {
		origin = vector<int>(n + 1, 0);
		tree = vector<long long>(n + 1, 0);
	}

	void update(int pos, int value) {
		add(pos, (long long)value - origin[pos]);
		origin[pos] = value;
	}
	
	long long getRangeSum(int left, int right) {
		return pSum(right) - pSum(left - 1);
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, a, b, c;
	cin >> n >> m;
	penwick p(n);
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		if (a == 0) cout << p.getRangeSum(min(b, c), max(b, c)) << "\n";
		else p.update(b, c);
	}
	return 0;
}