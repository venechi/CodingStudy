#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> queenPos;

bool available(int x, int y) {
	for (int i = 1; i <= x; ++i) {
		if (queenPos[x - i] == y - i || queenPos[x - i] == y + i || queenPos[x - i] == y) return false;
	}
	return true;
}

int rec_func(int k) {
	if (k == N) return 1;
	else {
		int sum = 0;
		for (int i = 0; i < N; ++i) {
			if (available(k, i)) {
				queenPos[k] = i;
				sum += rec_func(k + 1);
			}
		}
		return sum;
	}
}

int main(void) {
	cin >> N;
	queenPos = vector<int>(N, -1);
	cout << rec_func(0) << endl;
	return 0;
}