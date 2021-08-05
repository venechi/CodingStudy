#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> lis;

int find_pos(int target) {
	int low = 1, mid, high = lis.size();
	while (low < high) {
		mid = (low + high) / 2;
		if (lis[mid] == target) return mid;
		if (lis[mid] > target) high = mid;
		else low = mid + 1;
	}
	return low;
}


int main(void) {
	ios::sync_with_stdio(false);
	int n, len = 0;
	cin >> n;
	vector<int> numbers(n);
	lis = vector<int>(n + 1, 1000001);
	lis[0] = 0;
	for (int i = 0; i < n; ++i)cin >> numbers[i];
	for (int i = 0; i < n; ++i) {
		int pos = find_pos(numbers[i]);
		if (lis[pos] > numbers[i]) {
			lis[pos] = numbers[i];
			len = max(len, pos);
		}
	}
	cout << len << endl;
	return 0;
}
