#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<pair<int,int>> friends;

int calc(vector<bool> taken) {
	int cnt = 0;
	int pos = -1;
	for (int i = 0; i < taken.size(); ++i) {
		if (!taken[i]) {
			pos = i; break;
		}
	}
	if (pos == -1) return 1;
	for (int i = pos + 1; i < taken.size(); ++i) {
		if (!taken[i]) {
			if (friends.find({ pos, i }) != friends.end()) {
				taken[pos] = taken[i] = true;
				cnt += calc(taken);
				taken[pos] = taken[i] = false;
			}
		}
	}
	return cnt;
}

int main(void) {
	int tc, n, m, a, b;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cin >> n >> m;
		friends.clear();
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			friends.insert({ min(a,b),max(a,b) });
		}
		vector<bool> taken(n, false);
		cout << calc(taken) << endl;
	}
	return 0;
}