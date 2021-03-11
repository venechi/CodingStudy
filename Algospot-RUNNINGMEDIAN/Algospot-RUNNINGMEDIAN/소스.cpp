#include <iostream>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

const int MOD = 20090711;

//���� ������
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
			//seed * a���� unsigned int�� ǥ�� ������ �Ѿ �� �����Ƿ� unsigned long long int ���
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
		//���� ū ���� �������� �켱���� ť
		priority_queue<int> big;
		//���� ���� ���� �������� �켱���� ť
		priority_queue<int, vector<int>, greater<int>> small;
		result = 0;
		//���ĵ� �迭�� ���� ������ big��, ���� ������ small�� ����ְ� �����Ѵ�
		//���ĵ� �迭 ������ ������ Ȧ���� ��� ����+1���� ���Ҹ� big�� �ִ´�.
		do {
			//big�� small�� ���� ��Ģ�� ������ �� �ֵ��� �� ���Ҹ� ����ִ´�.
			if (big.size() == small.size())
				big.push(input.getNext());
			else
				small.push(input.getNext());
			//������ ���� �����̸� �����Ѵ�.
			if (!small.empty() && (small.top() < big.top())) {
				temp = small.top();
				small.pop();
				small.push(big.top());
				big.pop();
				big.push(temp);
			}
			//(MOD - 1) * 2 �ص� int�� ǥ�� ������ ���� �����Ƿ� int������ ���
			result = (result + big.top()) % MOD;
		} while (--n);
		cout << result << "\n";
	} while (--testcase);
	return 0;
}