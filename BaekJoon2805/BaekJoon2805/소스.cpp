#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> lengthes;
int n, m;

bool check(int target) {
	int cnt = 0;
	int willGet;
	for (int i = 0; i < n; ++i) {
		willGet = lengthes[i] - target;
		if (willGet > 0) {
			cnt += willGet;
			if (cnt >= m) return true;
		}
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	lengthes = vector<int>(n);
	for (int i = 0; i < n; ++i)cin >> lengthes[i];
	int low = 0, mid, high = 2000000001;
	while (low < high) {
		mid = (low + high) / 2;
		if (check(mid)) low = mid + 1;
		else high = mid;
	}
	cout << low - 1 << endl;
	return 0;
}