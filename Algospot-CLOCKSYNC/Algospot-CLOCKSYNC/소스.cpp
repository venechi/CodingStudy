#include <iostream>
#include <vector>

using namespace std;

vector<int> clocks(16);
vector<vector<int>> switches = {
	{0,1,2},
	{3,7,9,11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};

void push(int depth) {
	for (int i = 0; i < switches[depth].size(); ++i) {
		clocks[switches[depth][i]] = (clocks[switches[depth][i]] + 3) % 12;
	}
}

bool isAllSet() {
	for (int i = 0; i < 16; ++i) {
		if (clocks[i] != 0) return false;
	}
	return true;
}

int calc(int depth) {
	if (isAllSet()) return 0;
	int answer = 41;
	if (depth >= 10) return answer;
	for (int i = 0; i < 4; ++i) {
		answer = min(answer, calc(depth + 1) + i);
		push(depth);
	}
	return answer;
}

int main(void) {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		for (int i = 0; i < 16; ++i) {
			cin >> clocks[i];
			clocks[i] %= 12;
		}
		int answer = calc(0);
		cout << (answer == 41 ? -1 : answer) << endl;
	}
	return 0;
}