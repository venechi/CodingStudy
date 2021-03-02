#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int score[10002];
string input;

int scoring(int s, int length) {
	bool check = true;
	//���ڰ� ���� ������ �̷� ��
	int gap = input.at(s + 1) - input.at(s);
	for (int i = 2; i < length; ++i) {
		if (input.at(s + i) - input.at(s + i - 1) != gap) {
			check = false;
			break;
		}
	}
	if (check) {
		//��� ���ڰ� ���� ��
		if (gap == 0)
			return 1;
		//���ڰ� 1�� ���� �����ϰų� ������ ��
		else if (gap == 1 || gap == -1)
			return 2;
		else
			return 5;
	}
	check = true;
	//�� ���� ���ڰ� �����ư��� ��Ÿ�� ��
	for (int i = 2; i < length; ++i) {
		gap *= -1;
		if (input.at(s + i) - input.at(s + i - 1) != gap) {
			check = false;
			break;
		}
	}
	if (check) return 4;
	//� Ư¡�� ���� ���
	return 10;
}

int getMinScore(int s) {
	int& ret = score[s];
	//�� �̻� ���� ���ڿ��� ������ 0 ��ȯ
	if (input.size() == s) return ret = 0;
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = 3; i < 6; ++i) {
		//���ڿ����� 3,4,5���ڸ� �߶��� ���� �����ظ� ���Ͽ� ���� ���� �� ��ȯ
		//�־��� ���ڿ��� 3�� �̸��� ��� ���ȣ�� �� ������ �Լ��� �������� ���ϹǷ� 987654321 ��ȯ
		if (s + i <= input.size())
			ret = min<int>(ret, scoring(s, i) + getMinScore(s + i));
	}
	return ret;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> input;
		memset(score, -1, sizeof(int) * 10000);
		cout << getMinScore(0) << endl;
	}
	return 0;
}