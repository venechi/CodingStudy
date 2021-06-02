#include <iostream>
#include <vector>

using namespace std;

vector<int> input;
vector<vector<int>> cache;

const int YET = -987654321;

int calc(int left, int right) {
	if (left > right) return 0;
	int& ret = cache[left][right];
	if (ret != YET) return ret;
	if (left == right) return ret = input[right];
	ret = max(ret, input[left] - calc(left + 1, right));
	ret = max(ret, input[right] - calc(left, right - 1));
	ret = max(ret, -calc(left + 2, right));
	ret = max(ret, -calc(left, right - 2));
	return ret;
}

int main(void) {
	int tc, n;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cin >> n;
		cache = vector<vector<int>>(n, vector<int>(n, YET));
		input = vector<int>(n);
		for (int i = 0; i < n; ++i) {
			cin >> input[i];
		}
		cout << calc(0, n - 1) << endl;
	}
	return 0;
}