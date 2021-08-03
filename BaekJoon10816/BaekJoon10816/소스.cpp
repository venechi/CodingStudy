#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;

int lBound(int target) {
	int low = 0, mid, high = arr.size();
	while (low < high) {
		mid = (low + high) / 2;
		if (arr[mid] >= target) high = mid;
		else low = mid + 1;
	}
	return low;
}

int uBound(int target) {
	int low = 0, mid, high = arr.size();
	while (low < high) {
		mid = (low + high) / 2;
		if (arr[mid] <= target) low = mid + 1;
		else high = mid;
	}
	return low - 1;
}

int main(void) {
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N;
	arr = vector<int>(N);
	for (int i = 0; i < N; ++i) cin >> arr[i];
	sort(arr.begin(), arr.end());
	cin >> M;
	vector<int> targets(M);
	for (int i = 0; i < M; ++i)cin >> targets[i];
	for (int i = 0; i < M; ++i)cout << uBound(targets[i]) - lBound(targets[i]) + 1 << "\n";
	return 0;
}