#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getPartialMatch(const string& s) {
	int begin = 1, matched = 0;
	vector<int> p(s.size(), 0);
	while (begin + matched < s.size()) {
		if (s[begin + matched] == s[matched]) {
			++matched;
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

int KMP(const string& a, const string& b) {
	if (a.size() < b.size()) return -1;
	int begin = 0, matched = 0;
	vector<int> p = getPartialMatch(b);
	while (begin + matched < a.size()) {
		if (a[begin + matched] == b[matched]) {
			++matched;
			if (matched == b.size()) return begin;
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
	return -1;
}

int main(void) {
	int testcase, n, result;
	cin >> testcase;
	string before, after;
	for (int i = 0; i < testcase; ++i) {
		result = 0;
		cin >> n;
		cin >> after;
		for (int j = 0; j < n; ++j) {
			before = after;
			cin >> after;
			if (j % 2 == 0)//시계방향
				result += KMP(after + after, before);
			else//반시계방향
				result += KMP(before + before, after);
		}
		cout << result << "\n";
	}
	return 0;
}