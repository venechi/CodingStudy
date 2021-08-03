#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int k, n;
vector<int> lengthes;

bool check(int target) {
	int sum = 0;
	for (int i = 0; i < k; ++i) {
		sum += (lengthes[i] / target);
		if (n <= sum) return true;
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> k >> n;
	lengthes = vector<int>(k);
	for (int i = 0; i < k; ++i)cin >> lengthes[i];
	sort(lengthes.begin(), lengthes.end());
	unsigned int low = 1, mid, high = lengthes.back() + 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (check(mid))low = mid + 1;
		else high = mid;
	}
	cout<< low - 1 <<endl;
	return 0;
}