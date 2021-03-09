#include <iostream>
#include <string>
#include <vector>

using namespace std;

//주어진 문자열 s의 역문자열 s`의 부분일치문자열을 구한다.
vector<int> getPartialMatch2(const string& s) {
	vector<int> p(s.size(), 0);
	int begin = 1, matched = 0;
	while (begin + matched < s.size()) {
		//문자열을 뒤에서부터 읽는다
		//begin과 matched는 일종의 offset역할을 하므로, begin과 matched를 계산하는 부분은 건드리지 않고,
		//begin과 matched를 이용하여 배열에 접근하는 부분만 수정하였다. (앞에서부터가 아니라 뒤에서부터 검사하도록)
		//나머지는 KMP 부분일치문자열 구하는 함수와 동일
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
	//주어진 문자열 s의 역문자열 s`의 부분일치 테이블
	vector<int> p = getPartialMatch2(s);
	//문자열 s와 역문자열 s`를 비교 (KMP 알고리즘 응용)
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