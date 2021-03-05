#include <iostream>
#include <queue>

using namespace std;

class RNG {
	//입력을 프로그램 내에서 생성함.
private:
	bool first = true;
	unsigned int value = 0;
public:
	unsigned int getNextValue() {
		if (first) {
			value = 1983u;
			first = false;
		}
		else value = value * 214013u + 2531011u;
		return (value % 10000) + 1;
	}
};

int main(void) {
	int testcase;
	int k, n;
	cin >> testcase;
	do {
		RNG input;
		cin >> k >> n;
		queue<unsigned int> q;
		unsigned int cnt = 0;
		int sum = 0;
		while (--n) {
			//모든 입력이 양수이므로, 부분합이 sum보다 커진 경우, 아무리 멀리 가 봐야 부분합이 이전보다 작아지는 경우는 없음
			//따라서 부분합이 k보다 작은 경우에만 새 원소를 받아 부분합에 추가
			if (sum < k) {
				q.push(input.getNextValue());
				sum += q.back();
			}
			//부분합이 k와 같은 경우, 이 경우를 cnt하고 부분합을 구성하는 맨 앞 원소 제거
			//부분합이 k보다 큰 경우, 부분합을 구성하는 맨 앞 원소를 제거하면서 부분합이 k와 같아지는지 비교
			//현재 부분합의 마지막 원소를 넣기 전엔 k보다 작았으므로, head가 현재와 같으면서 tail이 현 원소보다 이전에 있는 경우는 없음
			//따라서 head를 한칸씩 전진하면서 부분합이 k보다 작아지는지 검사.
			while (sum >= k) {
				if (sum == k) ++cnt;
				sum -= q.front();
				q.pop();
			}
		}
		cout << cnt << endl;
	} while (--testcase);
	return 0;
}