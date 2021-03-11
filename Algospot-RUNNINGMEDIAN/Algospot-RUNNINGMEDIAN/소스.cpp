#include <iostream>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

const int MOD = 20090711;

//난수 생성기
class RNG {
private:
	unsigned long long int seed = 1983;
	bool first = true;
	unsigned int a, b;
public:
	RNG(unsigned int a, unsigned int b) :a(a), b(b) {}
	unsigned int getNext() {
		if (first) {
			first = false;
			return seed;
		}
		else {
			//seed * a에서 unsigned int의 표현 범위를 넘어갈 수 있으므로 unsigned long long int 사용
			seed = (seed * a + b) % MOD;
			return seed;
		}
	}
};

int main(void) {
	int testcase, n, a, b, temp;
	unsigned int result;
	cin >> testcase;
	do {
		cin >> n >> a >> b;
		RNG input(a, b);
		//가장 큰 것을 내보내는 우선순위 큐
		priority_queue<int> big;
		//가장 작은 것을 내보내는 우선순위 큐
		priority_queue<int, vector<int>, greater<int>> small;
		result = 0;
		//정렬된 배열의 앞쪽 절반을 big에, 뒤쪽 절반을 small에 집어넣고 유지한다
		//정렬된 배열 원소의 개수가 홀수인 경우 절반+1개의 원소를 big에 넣는다.
		do {
			//big과 small의 개수 규칙을 유지할 수 있도록 새 원소를 집어넣는다.
			if (big.size() == small.size())
				big.push(input.getNext());
			else
				small.push(input.getNext());
			//정렬이 깨진 상태이면 조정한다.
			if (!small.empty() && (small.top() < big.top())) {
				temp = small.top();
				small.pop();
				small.push(big.top());
				big.pop();
				big.push(temp);
			}
			//(MOD - 1) * 2 해도 int의 표현 범위를 넘지 않으므로 int형으로 충분
			result = (result + big.top()) % MOD;
		} while (--n);
		cout << result << "\n";
	} while (--testcase);
	return 0;
}