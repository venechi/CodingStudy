#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, c;
vector<int> houses;

bool check(int target) {
	int prev = houses[0], cnt = 1;
	for (int i = 1; i < n; ++i) {
		if (houses[i] - prev >= target) {
			prev = houses[i];
			++cnt;
			if (cnt == c) return true;
		}
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> c;
	houses = vector<int>(n);
	for (int i = 0; i < n; ++i)cin >> houses[i];
	sort(houses.begin(), houses.end());
	int low = 0, mid, high = houses.back() + 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (check(mid)) low = mid + 1;
		else high = mid;
	}
	cout << low - 1 << endl;
	return 0;
}