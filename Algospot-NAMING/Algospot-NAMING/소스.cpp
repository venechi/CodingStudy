#include <iostream>
#include <string>
#include <vector>

using namespace std;

//KMP를 이용한 부분일치 테이블 생성
vector<int> getPartialMatch(string s) {
	vector<int> p(s.size(), 0);
	int begin = 1, matched = 0;
	while (begin + matched < s.size()) {
		if (s[begin + matched] == s[matched]) {
			++matched;
			//aaaabaa 문자열 예시
			//접두사 aa와 접미사 aa를 비교할 때, 접두사의 첫 a와 접미사의 마지막 a를 비교하는 것이 아니라 두 부분문자열의 첫 a끼리 비교하는 것임.
			//따라서 matched가 유지되는 동안 이전 계산결과가 누적됨.
			//양 끝단에서 검사해 오는 것이 아니라 각각의 시작점부터 누적 계산해 나가는 것임. (회문(palindrom) 검사와는 다름)
			//aaaabaa
			//||   ||
			//접두 접미
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
	//전체 문자열(언제나 일치)
	int k = p.size();
	//문자열의 길이가 0이면 중단.
	while (k != 0) {
		result.push_back(k);
		//현재 부분일치 문자열보다  길이가 작은 부분일치 문자열 중 가장 긴 부분일치 문자열을 찾는다.
		k = p[k - 1];
	}
	for (vector<int>::reverse_iterator it = result.rbegin(); it != result.rend(); ++it)
		cout << *it << " ";
	return 0;
}