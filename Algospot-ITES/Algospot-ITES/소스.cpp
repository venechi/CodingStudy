#include <iostream>
#include <queue>

using namespace std;

class RNG {
	//�Է��� ���α׷� ������ ������.
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
			//��� �Է��� ����̹Ƿ�, �κ����� sum���� Ŀ�� ���, �ƹ��� �ָ� �� ���� �κ����� �������� �۾����� ���� ����
			//���� �κ����� k���� ���� ��쿡�� �� ���Ҹ� �޾� �κ��տ� �߰�
			if (sum < k) {
				q.push(input.getNextValue());
				sum += q.back();
			}
			//�κ����� k�� ���� ���, �� ��츦 cnt�ϰ� �κ����� �����ϴ� �� �� ���� ����
			//�κ����� k���� ū ���, �κ����� �����ϴ� �� �� ���Ҹ� �����ϸ鼭 �κ����� k�� ���������� ��
			//���� �κ����� ������ ���Ҹ� �ֱ� ���� k���� �۾����Ƿ�, head�� ����� �����鼭 tail�� �� ���Һ��� ������ �ִ� ���� ����
			//���� head�� ��ĭ�� �����ϸ鼭 �κ����� k���� �۾������� �˻�.
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