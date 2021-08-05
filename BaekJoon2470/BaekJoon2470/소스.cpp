#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

////two pointer
//int main(void) {
//	int n;
//	cin >> n;
//	vector<int> nums(n);
//	for (int i = 0; i < n; ++i)cin >> nums[i];
//	sort(nums.begin(), nums.end());
//	int l = 0, r = nums.size() - 1;
//	int l1, l2, minimum = 2000000001;
//	int temp;
//	while (l < r) {
//		temp = nums[l] + nums[r];
//		if (abs(temp) < minimum) {
//			minimum = abs(temp);
//			l1 = nums[l];
//			l2 = nums[r];
//		}
//		if (temp == 0) break;
//		if (temp < 0) ++l;
//		else --r;
//	}
//	cout << l1 << " " << l2 << endl;
//	return 0;
// }

//binary search
int n;
vector<int> nums;

int findPos(int l, int target) {
	int low = l, mid, high = n;
	while (low < high) {
		mid = (low + high) / 2;
		if (nums[mid] >= target) high = mid;
		else low = mid + 1;
	}
	return low;
}

int main(void) {
	cin >> n;
	nums = vector<int>(n);
	for (int i = 0; i < n; ++i)cin >> nums[i];
	sort(nums.begin(), nums.end());
	int l1, l2, minimum = 2000000001;
	for (int i = 0; i < n; ++i) {
		int pos = findPos(i + 1, nums[i] * -1);
		int temp = 1;
		if (pos != n) {
			temp = nums[i] + nums[pos];
			if (abs(temp) < minimum) {
				minimum = abs(temp);
				l1 = nums[i];
				l2 = nums[pos];
			}
		}
		if (temp == 0) break;
		if (pos - 1 != i) {
			temp = nums[i] + nums[pos - 1];
			if (abs(temp) < minimum) {
				minimum = abs(temp);
				l1 = nums[i];
				l2 = nums[pos - 1];
			}
		}
		if (temp == 0) break;
	}
	cout << l1 << " " << l2 << endl;
	return 0;
}