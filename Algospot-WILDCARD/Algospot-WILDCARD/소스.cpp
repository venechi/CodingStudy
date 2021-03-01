#include <iostream>
#include <vector>
//sort용
#include <algorithm>
//memset용
#include <cstring>

using namespace std;

class MinerRegExp {
private:
	string pattern;
	string str;
	//글자수가 최대 100 cache[w][s]의 형태이며, 의미는 pattern의 (w,pattern.size()-1) 의 substring과 str의 (s, str.size()-1)의 substring이 match 되는지를 캐싱
	char cache[101][101];
	bool matcher(char w, char s) {
		//캐싱된 결과가 있으면 반환
		if (cache[w][s] != -1) return cache[w][s];
		//substring끼리 비교 시 첫 글자가 같은지 혹은 ?로 같게 처리되는지 비교, 나머지는 재귀호출로 처리
		if (w < pattern.size() && s < str.size() && (pattern[w] == '?' || pattern[w] == str[s])) return cache[w][s] = matcher(w + 1, s + 1);
		// pattern이 끝난 경우, str도 끝났는지 검사
		if (w == pattern.size()) return cache[w][s] = (s == str.size());
		// pattern의 substring의 첫 글자가 * 인경우, *에 추가로 한 글자를 할당할 것인지 검사 (할당하지 않는 경우 || (str의 substring이 남은 경우 && 할당하는 경우))
		if (pattern[w] == '*') return cache[w][s] = (matcher(w + 1, s) || (s < str.size() && matcher(w, s + 1)));
		// 그 외의 경우는 매칭 실패
		return cache[w][s] = false;
	}
public:
	MinerRegExp() {
		pattern = "";
		str = "";
	}
	void setPattern(string pattern) {
		this->pattern = pattern;	
	}
	void setFileName(string fileName) {
		this->str = fileName;
	}
	bool match() {
		memset(cache, -1, 101 * 101 * sizeof(char));
		return matcher(0, 0);
	}
};

int main(void) {
	int testcase = 0;
	string pattern, fileName;
	MinerRegExp reg;
	vector<string> answer;
	int n = 0;
	cin >> testcase;

	for (; testcase > 0; --testcase) {
		answer.clear();
		cin >> pattern;
		reg.setPattern(pattern);
		cin >> n;
		for (; n > 0; --n) {
			cin >> fileName;
			reg.setFileName(fileName);
			if (reg.match()) answer.push_back(fileName);
		}
		sort(answer.begin(), answer.end());
		for (vector<string>::iterator it = answer.begin(); it != answer.end(); ++it)
			cout << *it << endl;
	}

	return 0;
}