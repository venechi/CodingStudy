#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, bool>> track;
int numOfDurZero = 0;
int n, k;

void turn() {
	auto temp = track.back();
	track.pop_back();
	track.insert(track.begin(), temp);
	track[n - 1].second = false;
}

void moveRobots() {
	for (int i = n - 1; i > 0; --i) {
		if (!track[i].second && track[i].first > 0 && track[i - 1].second) {
			--track[i].first;
			track[i].second = true;
			track[i - 1].second = false;
			if (track[i].first == 0) ++numOfDurZero;
		}
	}
	track[n - 1].second = false;
}

void loadRobot() {
	if (track[0].first > 0) {
		--track[0].first;
		track[0].second = true;
		if (track[0].first == 0) ++numOfDurZero;
	}
}

int main(void) {
	int step = 0;
	cin >> n >> k;
	track = vector<pair<int, bool>>(n * 2, { 0,false });
	for (int i = 0; i < n * 2; ++i) cin >> track[i].first;
	while (true) {
		++step;
		turn();
		moveRobots();
		loadRobot();
		if (numOfDurZero >= k) break;
	}
	cout << step << endl;
	return 0;
}