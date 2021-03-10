#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct comparator {
	const vector<int> &group;
	int t;
	comparator(const vector<int>& group, const int t) :group(group), t(t) {}
	bool operator()(int a, int b) {
		if (group[a] != group[b]) return group[a] < group[b];
		else return group[a + t] < group[b + t];
	}
}comparator;

//suffix�� ���ĵ� suffix�迭�� �����.
void getSuffixArray(const string& s, vector<int>& suffix) {
	int n = s.size();
	//���̻�s[i...]�� �׷�
	vector<int> a(n + 1), b(n + 1);
	vector<int>* group = &a, * newGroup = &b, * temp;
	for (int i = 0; i < n; ++i) {
		suffix[i] = i;
		(*group)[i] = s[i];
	}
	(*group)[n] = -1;
	int t = 1;
	while (t < n) {
		comparator comp((*group), t);
		sort(suffix.begin(), suffix.end(), comp);
		t *= 2;
		if (t >= n) break;
		//�� ó�� �׷쿡 �׷��ȣ 0 �ο�
		(*newGroup)[suffix[0]] = 0;
		//�񱳿��� �� ����ó���� ���ֱ� ���� �������� �׷��ȣ -1 ����
		//������ �ڸ��� �������Ѵٴ� ����, ������ �ڸ��� �������� �� ����� �ٸ� �� ��󺸴� ���̰� ª�ٴ� �̾߱��̹Ƿ� ������ ������ ������ ����
		//-1�̶�� �ſ� ���� ���� �Ҵ���.(���� �׷� ��ȣ�� 0�̹Ƿ� -1�̸� ������ ��� ����� �׷��ȣ���� ����)
		(*newGroup)[n] = -1;
		for (int i = 1; i < n; ++i) {
			if (comp(suffix[i - 1], suffix[i]))
				(*newGroup)[suffix[i]] = (*newGroup)[suffix[i - 1]] + 1;
			else
				(*newGroup)[suffix[i]] = (*newGroup)[suffix[i - 1]];
		}
		temp = group;
		group = newGroup;
		newGroup = temp;
	}
}

int maxPrefixLength(const string& s, int start, int end) {
	int k = 0, n = s.size();
	while (start < n && end < n && s[start] == s[end]) {
		++start; ++end; ++k;
	}
	return k;
}

int habit(const int k, const string& s) {
	int n = s.size();
	if (k == 1) return n;
	int ret = 0;
	vector<int> suffix(n);
	getSuffixArray(s, suffix);
	for (int i = 0; i + k <= n; ++i)
		ret = max(ret, maxPrefixLength(s, suffix[i], suffix[i + k - 1]));
	return ret;
}

//�������� �� ���縦 �������� ������ Ÿ�Ӿƿ���.
int main(void) {
	int testcase, k;
	string input;
	cin >> testcase;
	do {
		cin >> k >> input;
		cout << habit(k, input) << "\n";
	} while (--testcase);
	return 0;
}