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
		//���� �Ѹ�
		sum = 1;
		participants.clear();
		cin >> x >> y;
		//���� �Ѹ��� ������ ����
		participants[x] = y;
		while (--n) {
			cin >> x >> y;
			it = participants.upper_bound(x);
			//������ �� Ǭ ���� ���� �� ���� �ĺ��ں��� ���� ����� ���ų�, �� ���� ������ Ǭ �����ڰ� ������ ���� ��� �׸� ���� ���� ���
			if ((it == participants.end()) || ((*it).second < y)) {
				//�� ������ ���
				participants[x] = y;
				//�� �����ں��� Ǭ ���� ���� ���� ��� ���� ���� ���� �����ڵ� ����
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
			//���� ���� �ο� ������Ʈ
			sum += participants.size();
		}
		cout << sum << "\n";
	} while (--testcase);
	return 0;
}