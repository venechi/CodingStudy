#include <iostream>
#include <vector>

using namespace std;

vector<long long> nums;
vector<long long> penwik;

void update(int pos, long long diff) {
	nums[pos] += diff;
	for (int i = pos; i < penwik.size(); i = i + (i & -i)) {
		penwik[i] += diff;
	}
}

long long getPsum(int end) {
	long long sum = 0;
	for (int i = end; i > 0; i = i - (i & -i)) {
		sum += penwik[i];
	}
	return sum;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	penwik = vector<long long>(n + 1, 0);
	nums = vector<long long>(n + 1);
	int l;
	for (int i = 0; i < n; ++i) {
		cin >> l;
		update(i + 1, l);
	}
	long long a, b, c;
	for (int i = 0; i < m + k; ++i) {
		cin >> a >> b >> c;
		if (a == 1) {
			update(b, c - nums[b]);
		}
		else {
			cout << getPsum(c) - getPsum(b - 1) << "\n";
		}
	}
	return 0;
}