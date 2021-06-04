#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<double> posts;

bool check(double gap) {
	int cameras = 1;
	int limit = posts[0] + gap;
	for (int i = 1; i < m; ++i) {
		if (posts[i] >= limit) {
			++cameras;
			if (cameras == n) return true;
			limit = posts[i] + gap;
		}
	}
	return false;
}

double calc() {
	int low = 0;
	int high = 240000;
	int mid;
	for (int i = 0; i < 18; ++i) {
		mid = (low + high) / 2;
		if (check(mid))low = mid;
		else high = mid;
	}
	return (double)low / 1000;
}

int main(void) {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cin >> n >> m;
		posts = vector<double>(m);
		for (int i = 0; i < m; ++i) {
			cin >> posts[i];
			posts[i] *= 1000;
		}
		printf_s("%0.2f\n", calc());
	}
	return 0;
}