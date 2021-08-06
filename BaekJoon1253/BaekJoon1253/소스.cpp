#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nums;

bool check(int targetPos) {
	int target = nums[targetPos];
	int l = 0, r = nums.size() - 1;
	while (l < r) {
		if (l == targetPos) ++l;
		else if (r == targetPos) --r;
		else {
			if (nums[l] + nums[r] == target) return true;
			if (nums[l] + nums[r] > target) --r;
			else ++l;
		}
	}
	return false;
}

int main(void) {
	int n;
	cin >> n;
	nums = vector<int>(n);
	for (int i = 0; i < n; ++i)cin >> nums[i];
	sort(nums.begin(), nums.end());
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (check(i)) ++cnt;
	}
	cout << cnt << endl;
	return 0;
}

//bool bSearch(int start, int target, int avoid1, int avoid2) {
//	int low = start, mid, high = nums.size();
//	while (low < high) {
//		mid = (low + high) / 2;
//		if (nums[mid] == target) {
//			for (int pos = mid; pos >= 0 && nums[pos] == nums[mid]; --pos) {
//				if (pos != avoid1 && pos != avoid2) return true;
//			}
//			for (int pos = mid + 1; pos < nums.size() && nums[pos] == nums[mid]; ++pos) {
//				if (pos != avoid1 && pos != avoid2) return true;
//			}
//			break;
//		}
//		if (nums[mid] > target) high = mid;
//		else low = mid + 1;
//	}
//	return false;
//}
//
//int main(void) {
//	int n;
//	int cnt = 0;
//	cin >> n;
//	nums = vector<int>(n);
//	for (int i = 0; i < n; ++i)cin >> nums[i];
//	sort(nums.begin(), nums.end());
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (i == j) continue;
//			if (bSearch(j + 1, nums[i] - nums[j], i, j)) {
//				++cnt;
//				break;
//			}
//		}
//	}
//	cout << cnt << endl;
//	return 0;
//}