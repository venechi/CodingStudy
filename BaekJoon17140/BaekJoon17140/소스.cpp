#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

int main(void) {
	int r, c, k;
	cin >> r >> c >> k;
	vector<vector<int>> arr(3, vector<int>(3, 0));
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j)cin >> arr[i][j];
	int sec = 0;
	bool applyR = true;
	for (; sec <= 100; ++sec) {
		if (r <= arr.size() && c <= arr[r - 1].size() && arr[r - 1][c - 1] == k) {
			cout << sec;
			return 0;
		}
		if (applyR) {
			int maxLength = -1;
			for (int i = 0; i < arr.size(); ++i) {
				vector<int> cnt(101, 0);
				for (int j = 0; j < arr[i].size(); ++j) cnt[arr[i][j]]++;
				vector < pair<int, int>> container;
				for (int i = 1; i < cnt.size(); ++i) {
					if (cnt[i] != 0) {
						container.push_back({ i, cnt[i] });
					}
				}
				sort(container.begin(), container.end(), cmp);
				arr[i] = vector<int>(container.size() * 2);
				for (int k = 0; k < container.size(); ++k) {
					arr[i][k*2] = container[k].first;
					arr[i][k * 2 + 1] = container[k].second;
				}
				maxLength = max(maxLength, (int)arr[i].size());
			}
			maxLength = min(maxLength, 100);
			for (int i = 0; i < arr.size(); ++i) {
				arr[i].resize(maxLength);
			}
			applyR = (maxLength <= arr.size());
		}
		else {
			int maxLength = -1;
			for (int i = 0; i < arr[0].size(); ++i) {
				vector<int> cnt(101, 0);
				for (int j = 0; j < arr.size(); ++j) cnt[arr[j][i]]++;
				vector < pair<int, int>> container;
				for (int i = 1; i < cnt.size(); ++i) {
					if (cnt[i] != 0) {
						container.push_back({ i, cnt[i] });
					}
				}
				sort(container.begin(), container.end(), cmp);
				maxLength = max(maxLength, (int)container.size() * 2);
				for (int i = arr.size(); i < maxLength; ++i)arr.push_back(vector<int>(arr[0].size()));
				for (int j = 0; j < container.size(); ++j) {
					arr[j * 2][i] = container[j].first;
					arr[j * 2 + 1][i] = container[j].second;
				}
				for (int j = container.size()*2; j < arr.size(); ++j) arr[j][i] = 0;
			}
			maxLength = min(maxLength, 100);
			for (int i = maxLength; i < arr.size(); ++i)arr.pop_back();
			applyR = (maxLength >= arr[0].size());
		}
	}
	cout << -1;
	return 0;
}