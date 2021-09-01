#include <iostream>
#include <vector>

using namespace std;

class mergeSort {
private:
	vector<int> arr;
	vector<int> temp;
	long long sort(int left, int right) {
		if (left + 1 == right) return 0;
		else {
			int mid = (left + right) / 2;
			long long cnt = 0;
			cnt += sort(left, mid);
			cnt += sort(mid, right);
			int lp = left, rp = mid;
			while(lp < mid || rp < right) {
				int tempPos = lp + rp - mid;
				if (lp == mid) temp[tempPos] = arr[rp++];
				else if (rp == right) temp[tempPos] = arr[lp++];
				else {
					if (arr[lp] <= arr[rp]) temp[tempPos] = arr[lp++];
					else {
						temp[tempPos] = arr[rp++];
						cnt += (mid - lp);
					}
				}
			}
			for (int i = left; i < right; ++i) arr[i] = temp[i];
			return cnt;
		}
	}

public:
	mergeSort(const vector<int>& arr) {
		this->arr = arr;
		temp = vector<int>(arr.size());
	}

	long long getSwapCnt() {
		return sort(0, arr.size());
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)cin >> arr[i];
	mergeSort m(arr);
	cout << m.getSwapCnt();
	return 0;
}