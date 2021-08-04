#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;

long long cnt_less(int target) {
	long long cnt = 0;
	for (int i = 1; i <= n; ++i) {
		cnt += min(n, target / i);
	}
	return cnt;
}

int getKth() {
	int low = 1, mid, high = int(min((long long)n * n, 1000000000LL)) + 1;
	while (low < high) {
		mid = (low + high) / 2;
		long long cnt = cnt_less(mid);

		if (cnt < k) low = mid + 1;
		else high = mid;
	}
	return low;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	cout << getKth() << endl;
	return 0;
}