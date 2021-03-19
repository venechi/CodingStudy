#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_LENGTH = 8;
vector<int> original(MAX_LENGTH);
map<vector<int>, int> depth;

//2,1,0 배열을 원복하는데 필요한 비용과
//2,1,0,3,4,5,6,7 배열(2,1,0 이후는 정렬되어있음)을 원복하는데 필요한 비용은 같으므로
//입력 가능한 최대 길이의 배열의 가능 비용을 계산한 뒤
//최대 길이보다 짧은 배열이 입력으로 들어오면
//짧은 길이만큼 정렬된 배열을 뒤에 이어붙여서 필요비용을 산출한다
//따라서 preCalc는 한번만 계산하면 된다.
void preCalc() {
	vector<int> here = original;
	queue<vector<int>> Q;
	depth[here] = 0;
	Q.push(here);
	while (!Q.empty()) {
		here = Q.front();
		Q.pop();
		int cost = depth[here];
		for (int i = 0; i < MAX_LENGTH - 1; ++i) {
			for (int j = i + 2; j <= MAX_LENGTH; ++j) {
				reverse(here.begin() + i, here.begin() + j);
				if (depth.count(here) == 0) {
					depth[here] = cost + 1;
					Q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}

int main(void) {
	int testcase, n, cnt;
	cin >> testcase;
	for (int i = 0; i < MAX_LENGTH; ++i)
		original[i] = i;
	preCalc();
	do {
		cin >> n;
		vector<int> input(n);
		for (int i = 0; i < n; ++i) {
			cin >> input[i];
		}
		vector<int> processed = original;
		for (int i = 0; i < n; ++i) {
			cnt = 0;
			for (int j = 0; j < n; ++j)
				if (input[i] > input[j])++cnt;
			processed[i] = cnt;
		}
		cout << depth[processed] << "\n";
	} while (--testcase);
	return 0;
}