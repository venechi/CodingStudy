#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int r, c;
vector<vector<char>> map;

vector<pair<int, int>> coords = {
	       {-1,0},
	{0,-1},       {0,1},
	        {1,0}
};

class cmp {
public:
	bool operator() (const vector<int>& a, const vector<int>& b) {
		return a[0] > b[0];
	}
};

void spreadWater() {
	queue<pair<int, int>> q;
	for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (map[i][j] == '*') q.push({ i,j });
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int i = 0; i < coords.size(); ++i) {
			int calX = cur.first + coords[i].first, calY = cur.second + coords[i].second;
			if (calX < 0 || calX >= r || calY < 0 || calY >= c) continue;
			if (map[calX][calY] == '.') {
				map[calX][calY] = '*';
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> r >> c;
	map = vector<vector<char>>(r, vector<char>(c));
	vector<vector<bool>> visited(r, vector<bool>(c, false));
	priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
	string input;
	for (int i = 0; i < r; ++i) {
		cin >> input;
		for (int j = 0; j < c; ++j) {
			map[i][j] = input[j];
			if (map[i][j] == 'S') {
				map[i][j] = '.';
				pq.push({ 0,i,j });
				visited[i][j] = true;
			}
		}
	}
	int min = -1;
	bool success = false;
	while(!pq.empty()) {
		vector<int> cur = pq.top(); pq.pop();
		if (map[cur[1]][cur[2]] == 'D') {
			cout << cur[0] << "\n";
			success = true;
			break;
		}
		if (cur[0] != min) {
			spreadWater();
			++min;
		}
		for (int i = 0; i < coords.size(); ++i) {
			int calX = cur[1] + coords[i].first, calY = cur[2] + coords[i].second;
			if (calX < 0 || calX >= r || calY < 0 || calY >= c) continue;
			
			if (map[calX][calY] == '.' || map[calX][calY] == 'D') {
				if (!visited[calX][calY]) {
					visited[calX][calY] = true;
					pq.push({ cur[0] + 1, calX,calY });
				}
			}
		}
	}
	if (!success) cout << "KAKTUS" << endl;
	return 0;
}