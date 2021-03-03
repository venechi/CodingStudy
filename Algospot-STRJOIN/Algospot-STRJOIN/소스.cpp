#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	int testcase, n, a, b, temp, result;
	//ǥ�� �켱���� ť greater<int>�� ������� ���� ���� ���Ұ� top�� �ִ� �켱���� ť�� �ȴ�.(�⺻���� std::less<T>)
	priority_queue<int, vector<int>, greater<int>> queue;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> temp;
			queue.push(temp);
		}
		result = 0;
		//���� ���� ������ ���ڿ� 2���� ��ġ�� ���� �ּҺ���� �ȴ�.
		//���� ��ģ ���ڿ��� ����� ������ ���ڿ��� �ٸ� ���ڿ��� ������ ������ �ٽ� ȣ��Ǵ� �����̱� ����.
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