#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//제일 왼쪽을 고정한 뒤, 남은 두 부분에 투 포인터 적용
//O(N^2)
int main(void) {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> liqid(n);
	for (int i = 0; i < n; ++i)cin >> liqid[i];
	sort(liqid.begin(), liqid.end());
	int l = 0, r = n - 1;
	vector<long long> opt = { 3000000001 };
	for (int i = 0; i < n - 2; ++i) {
		int l = i + 1, r = n - 1;
		while (l < r) {
			long long sum = (long long)liqid[i] + liqid[l] + liqid[r];
			if (abs(opt[0]) > abs(sum)) {
				opt = { abs(sum), liqid[i], liqid[l], liqid[r] };
			}
			if (sum < 0) ++l;
			else --r;
		}
	}
	cout << opt[1] << " " << opt[2] << " " << opt[3] << endl;
	return 0;
}