#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> s;

vector<int> teamStart(1,0);
vector<int> teamLink(1,0);

int rec_func(int k) {
	if (k == N) return abs(teamStart[0] - teamLink[0]);
	else {
		int add = 0, ifChooseStart = 987654321, ifChooseLink = 987654321;
		if (teamLink.size() < N / 2 + 1) {
			for (int i = 1; i < teamLink.size(); ++i) {
				add = add + s[teamLink[i]][k] + s[k][teamLink[i]];
			}
			teamLink[0] += add;
			teamLink.push_back(k);
			ifChooseLink = rec_func(k + 1);
			teamLink.pop_back();
			teamLink[0] -= add;
		}
		add = 0;
		if (teamStart.size() < N / 2 + 1) {
			for (int i = 1; i < teamStart.size(); ++i) {
				add = add + s[teamStart[i]][k] + s[k][teamStart[i]];
			}
			teamStart[0] += add;
			teamStart.push_back(k);
			ifChooseStart = rec_func(k + 1);
			teamStart.pop_back();
			teamStart[0] -= add;
		}
		return min(ifChooseLink, ifChooseStart);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> N;
	s = vector<vector<int>>(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> s[i][j];
	cout << rec_func(0) << endl;
	return 0;
}