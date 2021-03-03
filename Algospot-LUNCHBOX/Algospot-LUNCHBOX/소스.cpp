#include <iostream>
#include <algorithm>

using namespace std;

int n;
pair<int, int> boxes[10000];

int main(void) {
	int testcase, elapsedTime, microWaving;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> boxes[i].first;
		for (int i = 0; i < n; ++i)
			cin >> boxes[i].second;
		//먹는 시간이 가장 긴 도시락을 가장 빨리 데워야 점심시간을 최소화 할 수 있다.
		sort(boxes, boxes + n, [](pair<int, int> a, pair<int, int> b) {return a.second > b.second; });
		elapsedTime = microWaving = 0;
		for (int i = 0; i < n; ++i) {
			//전자레인지는 하나지만 먹는건 동시에 여러명이 먹을 수 있으므로
			//i번째 도시락까지 데우고 먹는 시간과 이전에 데웠던 도시락을 다 먹게 되는 시간을 비교하여 더 큰 값을 취해야 한다.
			elapsedTime = max<int>(elapsedTime, boxes[i].first + boxes[i].second + microWaving);
			microWaving += boxes[i].first;
		}
		cout << elapsedTime << endl;
	} while (--testcase);
	return 0;
}