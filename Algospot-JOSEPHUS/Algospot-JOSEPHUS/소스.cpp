#include <iostream>
#include <list>

using namespace std;

int main(void) {
	int testcase;
	int n, k;
	cin >> testcase;
	do {
		cin >> n >> k;
		list<int> people;
		for (int i = 0; i < n; ++i)
			people.push_back(i + 1);
		list<int>::iterator kill = people.begin();
		//people.erase(people.end())�� ����ÿ��� ����Ʈ�� ��� ������ ���ư��� �� �ϴ�.
		//�� �̻� people ������ ���������� ������ �� ���Եȴ�.
		//����Լ��� ������ �ϴ� �� �ϳ�, ���� ������ ������ �Ұ����ϸ�, ��Ÿ�� ������ ���� ��������(�ּ������� ���ư��� �׷� �� �ϴ�)
		while (people.size() > 2) {
			kill = people.erase(kill);
			if (kill == people.end()) kill = people.begin();
			for (int i = 1; i < k; ++i) {
				++kill;
				if (kill == people.end()) kill = people.begin();
				//���� ���� ��ó�� people.end()�� erase�Լ��� ���������� �ʵ��� ����
			}
		}
		cout << people.front() << " " << people.back() << endl;
	} while (--testcase);
	return 0;
}