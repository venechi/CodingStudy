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

//suffix에 정렬된 suffix배열을 담아줌.
void getSuffixArray(const string& s, vector<int>& suffix) {
	int n = s.size();
	//접미사s[i...]의 그룹
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
		//맨 처음 그룹에 그룹번호 0 부여
		(*newGroup)[suffix[0]] = 0;
		//비교연산 시 예외처리를 없애기 위해 마지막에 그룹번호 -1 삽입
		//마지막 자리에 엑세스한다는 것은, 마지막 자리에 엑세스한 비교 대상이 다른 비교 대상보다 길이가 짧다는 이야기이므로 무조건 앞으로 보내기 위해
		//-1이라는 매우 작은 값을 할당함.(최초 그룹 번호가 0이므로 -1이면 가능한 모든 경우의 그룹번호보다 작음)
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

//쓸데없는 값 복사를 억제하지 않으면 타임아웃됨.
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