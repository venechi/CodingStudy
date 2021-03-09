#include <iostream>
#include <string>
#include <vector>

using namespace std;

//�־��� ���ڿ� s�� �����ڿ� s`�� �κ���ġ���ڿ��� ���Ѵ�.
vector<int> getPartialMatch2(const string& s) {
	vector<int> p(s.size(), 0);
	int begin = 1, matched = 0;
	while (begin + matched < s.size()) {
		//���ڿ��� �ڿ������� �д´�
		//begin�� matched�� ������ offset������ �ϹǷ�, begin�� matched�� ����ϴ� �κ��� �ǵ帮�� �ʰ�,
		//begin�� matched�� �̿��Ͽ� �迭�� �����ϴ� �κи� �����Ͽ���. (�տ������Ͱ� �ƴ϶� �ڿ������� �˻��ϵ���)
		//�������� KMP �κ���ġ���ڿ� ���ϴ� �Լ��� ����
		if (s[s.size() - 1 - (begin + matched)] == s[s.size() - 1 - matched]) {
			++matched;
			p[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin = begin + matched - p[matched - 1];
				matched = p[matched - 1];
			}
		}
	}
	return p;
}

int minPal2(const string& s) {
	int begin = 0, matched = 0;
	//�־��� ���ڿ� s�� �����ڿ� s`�� �κ���ġ ���̺�
	vector<int> p = getPartialMatch2(s);
	//���ڿ� s�� �����ڿ� s`�� �� (KMP �˰��� ����)
	while (begin + matched < s.size()) {
		if (s[begin + matched] == s[s.size() - 1 - matched])
			++matched;
		else {
			if (matched == 0)
				++begin;
			else {
				begin = begin + matched - p[matched - 1];
				matched = p[matched - 1];
			}
		}
	}
	return s.size() * 2 - matched;
}

int main(void) {
	int testcase;
	string input;
	cin >> testcase;
	for (int i = 0; i < testcase; --testcase) {
		cin >> input;
		cout << minPal2(input) << endl;
	}
	return 0;
}