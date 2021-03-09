#include <iostream>
#include <string>
#include <vector>

using namespace std;

//KMP�� �̿��� �κ���ġ ���̺� ����
vector<int> getPartialMatch(string s) {
	vector<int> p(s.size(), 0);
	int begin = 1, matched = 0;
	while (begin + matched < s.size()) {
		if (s[begin + matched] == s[matched]) {
			++matched;
			//aaaabaa ���ڿ� ����
			//���λ� aa�� ���̻� aa�� ���� ��, ���λ��� ù a�� ���̻��� ������ a�� ���ϴ� ���� �ƴ϶� �� �κй��ڿ��� ù a���� ���ϴ� ����.
			//���� matched�� �����Ǵ� ���� ���� ������� ������.
			//�� ���ܿ��� �˻��� ���� ���� �ƴ϶� ������ ���������� ���� ����� ������ ����. (ȸ��(palindrom) �˻�ʹ� �ٸ�)
			//aaaabaa
			//||   ||
			//���� ����
			p[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				++begin;
			else {
				begin = begin + matched - p[matched - 1];
				matched = p[matched - 1];
			}
		}
	}
	return p;
}

int main(void) {
	string father, mother;
	cin >> father >> mother;
	vector<int> result, p = getPartialMatch(father + mother);
	//��ü ���ڿ�(������ ��ġ)
	int k = p.size();
	//���ڿ��� ���̰� 0�̸� �ߴ�.
	while (k != 0) {
		result.push_back(k);
		//���� �κ���ġ ���ڿ�����  ���̰� ���� �κ���ġ ���ڿ� �� ���� �� �κ���ġ ���ڿ��� ã�´�.
		k = p[k - 1];
	}
	for (vector<int>::reverse_iterator it = result.rbegin(); it != result.rend(); ++it)
		cout << *it << " ";
	return 0;
}