#include <iostream>
#include <map>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	int testcase, n, x, y, sum;
	map<int, int> participants;
	map<int, int>::iterator it;
	cin >> testcase;
	do {
		cin >> n;
		//최초 한명
		sum = 1;
		participants.clear();
		cin >> x >> y;
		//최초 한명은 무조건 참가
		participants[x] = y;
		while (--n) {
			cin >> x >> y;
			it = participants.upper_bound(x);
			//참가자 중 푼 문제 수가 새 참가 후보자보다 많은 사람이 없거나, 더 많은 문제를 푼 참가자가 있지만 먹은 라면 그릇 수가 적은 경우
			if ((it == participants.end()) || ((*it).second < y)) {
				//새 참가자 등록
				participants[x] = y;
				//새 참가자보다 푼 문제 수와 먹은 라면 수가 적은 기존 참가자들 제거
				it = participants.lower_bound(x);
				while (it != participants.begin()) {
					--it;
					if (it->second < y)
						participants.erase(it);
					else
						break;
					it = participants.lower_bound(x);
				}
			}
			//참가 가능 인원 업데이트
			sum += participants.size();
		}
		cout << sum << "\n";
	} while (--testcase);
	return 0;
}