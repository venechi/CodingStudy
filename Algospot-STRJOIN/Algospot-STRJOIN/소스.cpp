#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	int testcase, n, a, b, temp, result;
	//표준 우선순위 큐 greater<int>의 사용으로 가장 작은 원소가 top에 있는 우선순위 큐가 된다.(기본값은 std::less<T>)
	priority_queue<int, vector<int>, greater<int>> queue;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> temp;
			queue.push(temp);
		}
		result = 0;
		//가장 작은 길이의 문자열 2개를 합치는 것이 최소비용이 된다.
		//먼저 합친 문자열의 비용이 합쳐진 문자열이 다른 문자열과 결합할 때마다 다시 호출되는 구조이기 때문.
		while (queue.size() > 1) {
			a = queue.top();
			queue.pop();
			b = queue.top();
			queue.pop();
			result += (a + b);
			queue.push(a + b);
		}
		cout << result << endl;
		queue.pop();
	} while (--testcase);
	return 0;
}