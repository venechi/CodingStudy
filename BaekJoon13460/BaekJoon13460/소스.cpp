#include <iostream>
#include <vector>

using namespace std;

const int INF = 987654321;

int n, m;
vector<vector<int>> map;

vector<pair<int, int>> coords = {
		  {-1,0},
	{0,-1},		 {0,1},
		   {1,0}
};

bool move(pair<int, int>& ball, int d) {
	bool moved = false;
	for (int next = map[ball.first + coords[d].first][ball.second + coords[d].second]; next != 1; ball.first += coords[d].first, ball.second += coords[d].second, next = map[ball.first + coords[d].first][ball.second + coords[d].second]) {
		moved = true;
		if (map[ball.first][ball.second] == 2) break;
	}
	return moved;
}

bool moveSequencially(pair<int, int>& ball1, pair<int, int>& ball2, int d) {
	bool moved = false;
	moved = move(ball1, d) || moved;
	if (map[ball1.first][ball1.second] != 2) {
		map[ball1.first][ball1.second] = 1;
		moved = move(ball2, d) || moved;
		map[ball1.first][ball1.second] = 0;
	}
	else moved = move(ball2, d) || moved;
	return moved;
}

bool gravity(vector<pair<int,int>>& balls, int d) {
	bool moved = false;
	if (balls[0].first == balls[1].first) {
		if (d == 1) {
			if (balls[0].second < balls[1].second)
				moved = moveSequencially(balls[0], balls[1], d);
			else moved = moveSequencially(balls[1], balls[0], d);
		}
		else if (d == 2) {
			if (balls[0].second < balls[1].second)
				moved = moveSequencially(balls[1], balls[0], d);
			else moved = moveSequencially(balls[0], balls[1], d);
		}
		else moved = moveSequencially(balls[0], balls[1], d);
	}
	else if (balls[0].second == balls[1].second) {
		if (d == 0) {
			if (balls[0].first < balls[1].first)
				moved = moveSequencially(balls[0], balls[1], d);
			else moved = moveSequencially(balls[1], balls[0], d);
		}
		else if (d == 3) {
			if (balls[0].first < balls[1].first)
				moved = moveSequencially(balls[1], balls[0], d);
			else moved = moveSequencially(balls[0], balls[1], d);
		}
		else moved = moveSequencially(balls[0], balls[1], d);
	}
	else moved = moveSequencially(balls[0], balls[1], d);
	return moved;
}

int getTries(vector<pair<int,int>> balls, int tryCnt) {
	if (tryCnt == 11) return INF;
	if (map[balls[1].first][balls[1].second] == 2) return INF;
	if (map[balls[0].first][balls[0].second] == 2) return tryCnt;
	int cnt = INF;
	for (int i = 0; i < 4; ++i) {
		vector<pair<int, int>> after = balls;
		if (gravity(after, i)) {
			cnt = min(cnt, getTries(after, tryCnt + 1));
		}
	}
	return cnt;
}

int main(void) {
	cin >> n >> m;
	//0: empty 1: wall 2: Goal
	map = vector<vector<int>>(n, vector<int>(m));
	vector<pair<int, int>> balls(2);
	string input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		for (int j = 0; j < m; ++j) {
			switch (input[j]) {
			case '.':
				map[i][j] = 0;
				break;
			case '#':
				map[i][j] = 1;
				break;
			case 'R':
				map[i][j] = 0;
				balls[0] = { i,j };
				break;
			case 'B':
				map[i][j] = 0;
				balls[1] = { i,j };
				break;
			case 'O':
				map[i][j] = 2;
				break;
			}
		}
	}
	int res = getTries(balls, 0);
	if (res == INF) cout << -1;
	else cout << res;
	return 0;
}