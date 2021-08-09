#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> numbers;
vector<vector<long long>> cache;

long long rec_func(int k, int sum) {
	if (sum < 0 || sum > 20) return 0;
	if (k == n - 1) return (sum == numbers[k] ? 1 : 0);
	long long& ret = cache[k][sum];
	if (ret != -1) return ret;
	else return ret = rec_func(k + 1, sum + numbers[k]) + rec_func(k + 1, sum - numbers[k]);
}

int main(void) {
	cin >> n;
	numbers = vector<int>(n);
	cache = vector<vector<long long>>(n - 1, vector<long long>(21, -1));
	for (int i = 0; i < n; ++i)cin >> numbers[i];
	//numbers[0]가 0일때 가능한 경우의 수가 2배가 되므로 주의
	cout << rec_func(1, numbers[0]) << endl;
	return 0;
}