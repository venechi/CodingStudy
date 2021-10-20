#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector<pair<int, int>> snailCoords = {
	{0,-1},{1,0},{0,1},{-1,0}
};
vector<pair<int, int>> coords = {
	{-1,0},{1,0},{0,-1},{0,1}
};
int centralX, centralY;
vector<vector<int>> mapper;
list<int> bids;

void makeCoords(const int n) {
	mapper = vector<vector<int>>(n, vector<int>(n));
	int x = centralX, y = centralY;
	int rad = 1, direction = 0;
	int step = 0, changeCnt = 0;
	for (int cnt = 0; cnt < n * n; ++cnt) {
		mapper[x][y] = cnt;
		if (step == rad) {
			direction = (direction + 1) % 4;
			step = 0;
			++changeCnt;
			if (changeCnt == 2) {
				changeCnt = 0;
				++rad;
			}
		}
		++step;
		x = x + snailCoords[direction].first, y = y + snailCoords[direction].second;
	}
}

void preProcess(const int n) {
	centralX = centralY = n / 2;
	makeCoords(n);
	vector<vector<int>> input(n, vector<int>(n));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j) cin >> input[i][j];
	vector<int> line(n * n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			line[mapper[i][j]] = input[i][j];
		}
	}
	bids = list<int>(line.begin(), line.end());
	bids.remove(0);
	bids.insert(bids.begin(), 0);
}

void attack(int d, int r) {
	int calX, calY;
	for (int i = r; i > 0; --i) {
		calX = centralX + coords[d - 1].first * i, calY = centralY + coords[d - 1].second * i;
		if (mapper[calX][calY] < bids.size()) {
			auto it = bids.begin();
			for (int j = 0; j < mapper[calX][calY]; ++j) ++it;
			bids.erase(it);
		}
	}
}

int explosion() {
	list<int>::iterator begin = bids.begin();
	int cnt = 1;
	int score = 0;
	for (list<int>::iterator it = ++bids.begin(); it != bids.end(); ++it) {
		if (*it == *begin) ++cnt;
		else {
			if (cnt >= 4) {
				score += ((*begin) * cnt);
				it = begin = bids.erase(begin, it);
			}
			else 
				begin = it;
			cnt = 1;
		}
	}
	if (cnt >= 4) {
		score += ((*begin) * cnt);
		bids.erase(begin, bids.end());
	}
	if (score > 0) score += explosion();
	return score;
}

void transform() {
	if (bids.size() <= 1) return;
	list<int> temp = bids;
	temp.erase(temp.begin());
	bids.clear();
	bids.push_back(0);
	list<int>::iterator begin = temp.begin();
	int cnt = 1;
	for (list<int>::iterator it = ++temp.begin(); it != temp.end(); ++it) {
		if (*it == *begin) ++cnt;
		else {
			bids.push_back(cnt);
			bids.push_back(*begin);
			begin = it;
			cnt = 1;
		}
	}
	bids.push_back(cnt);
	bids.push_back(*begin);
	if (bids.size() > mapper.size() * mapper.size()) {
		list<int>::iterator it = bids.begin();
		for (int i = 0; i < mapper.size() * mapper.size(); ++i) ++it;
		bids.erase(it, bids.end());
	}
}

int main(void) {
	int n, m, d, r, sum = 0;
	cin >> n >> m;
	preProcess(n);
	for (int i = 0; i < m; ++i) {
		cin >> d >> r;
		attack(d, r);
		sum += explosion();
		transform();
	}
	cout << sum << endl;
	return 0;
}