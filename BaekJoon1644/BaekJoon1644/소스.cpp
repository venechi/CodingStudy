#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(int n) {
	for (int i = 3; i <= sqrt(n); i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

int main(void) {
	int n;
	cin >> n;
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	vector<int> primes = { 2 };
	for (int i = 3; i <= n; i += 2) {
		if (isPrime(i)) primes.push_back(i);
	}
	int cnt = 0;
	int sum = 0;
	for (int l = 0, r = 0; r < primes.size(); ++r) {
		while (l < primes.size() && sum < n) {
			sum += primes[l++];
		}
		if (sum == n) ++cnt;
		sum -= primes[r];
	}
	cout << cnt << endl;
	return 0;
}