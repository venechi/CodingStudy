#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	vector<bool> has(100001, false);
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; ++i)cin >> nums[i];
	long long cnt = 0;
	int l = 0, r = 0;
	while (l < n) {
		while (r < n && !has[nums[r]]) {
			has[nums[r++]] = true;
		}
		cnt += (r - l);
		has[nums[l++]] = false;
	}
	cout << cnt << endl;
	return 0;
}