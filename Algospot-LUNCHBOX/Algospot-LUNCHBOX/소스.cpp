#include <iostream>
#include <algorithm>

using namespace std;

int n;
pair<int, int> boxes[10000];

int main(void) {
	int testcase, elapsedTime, microWaving;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> boxes[i].first;
		for (int i = 0; i < n; ++i)
			cin >> boxes[i].second;
		//�Դ� �ð��� ���� �� ���ö��� ���� ���� ������ ���ɽð��� �ּ�ȭ �� �� �ִ�.
		sort(boxes, boxes + n, [](pair<int, int> a, pair<int, int> b) {return a.second > b.second; });
		elapsedTime = microWaving = 0;
		for (int i = 0; i < n; ++i) {
			//���ڷ������� �ϳ����� �Դ°� ���ÿ� �������� ���� �� �����Ƿ�
			//i��° ���ö����� ����� �Դ� �ð��� ������ ������ ���ö��� �� �԰� �Ǵ� �ð��� ���Ͽ� �� ū ���� ���ؾ� �Ѵ�.
			elapsedTime = max<int>(elapsedTime, boxes[i].first + boxes[i].second + microWaving);
			microWaving += boxes[i].first;
		}
		cout << elapsedTime << endl;
	} while (--testcase);
	return 0;
}