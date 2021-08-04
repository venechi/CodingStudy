#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> map;
vector<pair<int, vector<int>>> students;

vector<pair<int, int>> coords = {
 	       {-1,0},
	{0,-1},      {0,1},
	       {1,0}
};

bool cmp(const vector<int>& a, const vector<int>& b) {
	if (a[0] == b[0]) {
		if (a[1] == b[1]) {
			if (a[2] == b[2]) {
				return a[3] < b[3];
			}
			else return a[2] < b[2];
		}
		else return a[1] > b[1];
	}
	else return a[0] > b[0];
}

vector<int> getLikeEmpty(int x, int y, const vector<int>& friends) {
	int calX, calY;
	int like = 0, empty = 0;
	for (int i = 0; i < coords.size(); ++i) {
		calX = x + coords[i].first;
		calY = y + coords[i].second;
		if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
		if (map[calX][calY] == 0) ++empty;
		else {
			for (int j = 0; j < friends.size(); ++j) {
				if (friends[j] == map[calX][calY]) {
					++like;
					break;
				}
			}
		}
	}
	return { like,empty };
}

void set(const pair<int, vector<int>>& student) {
	//liks_near, empty_near, x, y
	vector<vector<int>> possibles;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j] == 0) {
				auto seat = getLikeEmpty(i, j, student.second);
				seat.push_back(i);
				seat.push_back(j);
				possibles.push_back(seat);
			}
		}
	}
	sort(possibles.begin(), possibles.end(), cmp);
	map[possibles[0][2]][possibles[0][3]] = student.first;
}

int getSatisfaction(int x, int y) {
	int calX, calY, cnt = 0;
	const vector<int>& friends = students[map[x][y] - 1].second;
	for (int i = 0; i < coords.size(); ++i) {
		calX = x + coords[i].first;
		calY = y + coords[i].second;
		if (calX < 0 || calX >= n || calY < 0 || calY >= n) continue;
		for (int j = 0; j < friends.size(); ++j) {
			if (friends[j] == map[calX][calY]) {
				++cnt;
				break;
			}
		}
	}
	switch (cnt) {
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 10;
	case 3:
		return 100;
	case 4:
		return 1000;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n;
	map = vector<vector<int>>(n, vector<int>(n, 0));
	students = vector<pair<int, vector<int>>>(n * n, { 0, vector<int>(4,0) });
	for (int i = 0; i < n * n; ++i) {
		cin >> students[i].first;
		for (int j = 0; j < 4; ++j) cin >> students[i].second[j];
	}
	for (int i = 0; i < n * n; ++i) set(students[i]);
	sort(students.begin(), students.end());
	int total = 0;
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j) total += getSatisfaction(i, j);
	cout << total << endl;
	return 0;
}