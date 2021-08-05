#include <iostream>
#include <vector>

using namespace std;

vector<int> chars(26, 0);

int cnt() {
	int cnt = 0;
	for (int i = 0; i < chars.size(); ++i) {
		if (chars[i] > 0) ++cnt;
	}
	return cnt;
}

int main(void) {
	ios::sync_with_stdio(false);
	int n;
	string input;
	cin >> n >> input;
	int l = 0, r = 0;
	int maxCnt = 0;
	while (l < input.length()) {
		while (r < input.length()) {
			chars[input[r] - 'a']++;
			++r;
			if (cnt() <= n) maxCnt = max(maxCnt, r - l);
			else break;
		}
		chars[input[l] - 'a']--;
		++l;
	}
	cout << maxCnt << endl;
}