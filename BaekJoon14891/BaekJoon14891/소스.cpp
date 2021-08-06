#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> wheels(4, vector<int>(8));

int getScore() {
	int score = 0;
	for (int i = 0; i < 4; ++i) {
		if (wheels[i][0] == 1) {
			score += pow(2, i);
		}
	}
	return score;
}

//d=> true:clockwise false:reverse
void turn(int order, bool d, int prev) {
	if (order != 0 && order - 1 != prev) {
		if (wheels[order - 1][2] != wheels[order][6]) {
			turn(order - 1, !d, order);
		}
	}
	if (order != 3 && order + 1 != prev) {
		if (wheels[order + 1][6] != wheels[order][2]) {
			turn(order + 1, !d, order);
		}
	}
	if (d) {
		int temp = wheels[order].back();
		wheels[order].pop_back();
		wheels[order].insert(wheels[order].begin(), temp);
	}
	else {
		int temp = wheels[order][0];
		wheels[order].erase(wheels[order].begin());
		wheels[order].push_back(temp);
	}
}

int main(void) {
	string input;
	for (int i = 0; i < 4; ++i) {
		cin >> input;
		for (int j = 0; j < 8; ++j)wheels[i][j] = (input[j] - '0');
	}
	int k, order, d;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		cin >> order >> d;
		turn(order - 1, (d == 1), -1);
	}
	cout << getScore() << endl;
	return 0;
}